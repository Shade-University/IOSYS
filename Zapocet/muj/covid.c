// Operating Systems: sample code  (c) Tomáš Hudec
// Synchronization, Race Condition

// Modified: 2021-04-26

// Chování programu:
//
// Program načte ze standardního vstupu záznamy osob. Očekává se na každém řádku číslo skupiny
// (použité jako pořadové číslo vlny rezervací) a jméno osoby. Načítání je ukončeno první nastalou
// možností: konec vstupního souboru, nulové číslo skupiny, dosažení maximální kapacity.
//
// Pro každou osobu z načteného seznamu je vytvořeno vlákno simulující chování osoby:
// Po spuštění příslušné vlny očkování se pokusí zabrat první volnou pozici v pořadníku.
// Ukončení všech vln rezervací se synchronizuje se začátkem očkování, tj. s vláknem zdravotní sestry.
// Nevešla‑li se osoba do seznamu, vlákno se následně ukončí, jinak vyčkává na pozvánku k očkování,
// nechá se očkovat, vyčká na certifikát, opouští očkovací místo a zavolá domů.
//
// Vlákno zdravotní sestry na začátku čeká na dokončení všech vln rezervací. Pak podle pořadníku
// postupně zve pacienty, vyčká na jejich příchod, očkuje, vystavuje certifikát
// a nakonec čeká na opuštění místa právě naočkovaným pacientem.
// 
// Zadání:
//
// Upravte program tak, aby se vlákna chovala dle popsaného způsobu, tj.:
// • pořadník musí být korektně vyplňován,
// • začátek očkování se musí synchronizovat s ukončením všech rezervací ve funkci sync_vaccination_start,
// • pořadí očkování se musí držet pořadníku
// • a jednotlivé činnosti očkovaných osob a zdravotní sestry na sebe musejí korektně navazovat.
//
// Všechny proměnné musejí svým názvem vystihovat svůj účel.
// Je SILNĚ doporučeno držet se následujících pravidel pojmenovávání proměnných:
// • pro synchronizaci se používá prefix „sync“,
// • pro kritickou sekci se používá prefix „cs“,
// proměnná pro
// • synchronizaci začátku očkování s koncem rezervací obsahuje „vaccination“,
// • čekání pacienta obsahuje „patient“,
// • čekání zdravotní sestry obsahuje „nurse“,
// • řešení přístupu k pořadníku obsahuje „choosing“.
//
// Pozn.: Souběžné spouštění vláken v jednotlivých vlnách registrací je již vyřešeno
// pomocí podmínkových proměnných, vizte pole „sync_waves“.

#include <pthread.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <semaphore.h>

// convert a value of a macro to the string
#define STR_VAL(x)		STR(x)
#define STR(x)			#x

// ANSI color escape sequences
#define C_NORMAL	"\x1B[0m"
#define C_RED		"\x1B[1;31m"
#define C_DARK_RED	"\x1B[0;31m"
#define C_GREEN		"\x1B[1;32m"
#define C_BLUE		"\x1B[1;34m"
#define C_CYAN		"\x1B[1;36m"
#define C_MAGENTA	"\x1B[1;35m"
#define C_YELLOW	"\x1B[1;33m"
#define C_TITLE		C_MAGENTA
#define C_NAME		C_CYAN
#define C_NAME2		C_BLUE
#define C_FREE		C_GREEN
#define C_FAILED	C_DARK_RED
#define C_ERROR		C_RED
#define C_WAVE		C_RED
#define C_WAVE2		"\x1B[%d;31m"

#define MAXLEN_NAME	10			// max length of a name
#define MAX_PEOPLE	40			// max number of people
#define MAX_WAVES	3			// max number of waves
#define MAX_POSITIONS	30			// max reservation list size
#define NAME_FMT	"%" STR_VAL(MAXLEN_NAME) "s"

// people data type
typedef struct {
	int		group;			// group = 0 – end of list, group > 0 – a wave
	char		name[MAXLEN_NAME + 1];	// name and \0
} people_data_t;

people_data_t people_data[MAX_PEOPLE];		// people data (loaded from standard input)
int people;					// the number of people wanting to be vaccinated
int waves;					// the real number of groups (vaccination waves)
int wave_people[MAX_WAVES];			// the number of people in each wave

people_data_t vaccination_list[MAX_POSITIONS];	// list of reservations (filled by people threads)
int positions = MAX_POSITIONS;			// the number of positions in the vaccination list

// synchronization data type for a wave
typedef struct {
	bool		started;		// wave has been started
	pthread_cond_t	cond;			// to wait for start
	pthread_mutex_t	mutex;			// needed by cond
} sync_wave_t;

// all waves synchronization structures are initialized
sync_wave_t sync_waves[MAX_WAVES] = {
	{ false, PTHREAD_COND_INITIALIZER, PTHREAD_MUTEX_INITIALIZER },
	{ false, PTHREAD_COND_INITIALIZER, PTHREAD_MUTEX_INITIALIZER },
	{ false, PTHREAD_COND_INITIALIZER, PTHREAD_MUTEX_INITIALIZER },
};

// resources to solve the problem

// print specified list
void print_list(char *title, people_data_t list[], int max)
{
	int i;
	printf(C_TITLE "%s:" C_NORMAL "\n", title);
	for (i = 0; list[i].group > 0 && i < max; ++i)
		printf("%2d. " C_WAVE2 "%d" C_NORMAL " " C_NAME "%s" C_NORMAL "\n",
			i + 1, list[i].group % 2, list[i].group, list[i].name);
}

// release all resources that were initialized
void release_resources(void)
{
	int wave;

	// release barrier conditions and mutexes (static initialiation was used)
	for (wave = 0; wave < MAX_WAVES; ++wave) {
		if (pthread_cond_destroy(&sync_waves[wave].cond))
			perror("cond_destroy sync_waves");
		if (pthread_mutex_destroy(&sync_waves[wave].mutex))
			perror("mutex_destroy sync_waves");
	}
}

// 0 ≤ wave < MAX_WAVES
void sync_start_waves(int wave)
{
	// wait for wave simultaneous start by a broadcast wakeup
	pthread_mutex_lock(&sync_waves[wave].mutex);
	if (!sync_waves[wave].started)
		pthread_cond_wait(&sync_waves[wave].cond, &sync_waves[wave].mutex);
	pthread_mutex_unlock(&sync_waves[wave].mutex);
}

// synchronize nurse thread with all people threads after registration
void sync_vaccination_start(void)
{
			printf("Reservation finished.\n");	// printed once after synchronization
			print_list("Reservation list", vaccination_list, positions);
}

// just a simulation
void call_home(void)
{
	return;
}

void *do_registration_and_vaccination(void *arg)
{
#define	thread_id	(*(int *)arg)	// id of the thread, index to people_data[]
	int pos;

	// wait for a wave start, start all threads of the wave simultaneously
	sync_start_waves(people_data[thread_id].group - 1);

	// find first unset position and use it
	for (pos = 0; pos < positions && vaccination_list[pos].group > 0; ++pos);
	if (pos < positions) {	// a free spot found
		// take the position in the list
		vaccination_list[pos].group = people_data[thread_id].group;
		strncpy(vaccination_list[pos].name, people_data[thread_id].name, MAXLEN_NAME);
	}

	if (pos >= positions)
		printf(C_NAME NAME_FMT C_FAILED " (" C_WAVE "%d" C_FAILED ") "
			"didn't make it into the list" C_NORMAL "\n",
			people_data[thread_id].name,
			people_data[thread_id].group);

	// after all registering attempts, synchronize with the nurse thread
	sync_vaccination_start();

	// no free spot found: do not wait for vaccination, leave
	if (pos >= positions)
		return NULL;

	// vaccination

	printf(C_NAME NAME_FMT C_NORMAL " is going to take a vaccine\n", people_data[thread_id].name);

	printf(C_NAME2 NAME_FMT C_NORMAL " is leaving with a certificate\n", people_data[thread_id].name);

	call_home();	// call home: finished

	return NULL;
}
#undef thread_id

void *nurse(void *arg)
{
	int pos;

	sync_vaccination_start();

	printf("Vaccination is about to begin.\n");

	// list entries one by one
	for (pos = 0; pos < positions && vaccination_list[pos].group > 0; ++pos) {
		// invite a patient

		// prepare a vaccine, apply it, prepare a certificate
		printf(C_NAME2 NAME_FMT C_NORMAL " is taking a vaccine, then a nurse is filling a certificate\n",
			vaccination_list[pos].name);

		// patient left, continue with the next one
		printf(C_NAME2 NAME_FMT C_NORMAL " left\n", vaccination_list[pos].name);
	}

	return NULL;
}

// reads people data (group, name) and sets the number of them
// based on data: initializes the number of waves, and the number of people in each wave
void load_people(void)
{
	int rc;		// return code for scanf
	char c;		// detection of shortened names
	int shortened = 0;

	if (isatty(STDIN_FILENO))
		printf("Enter people data, one per line containing group id (1–%d, 0 to finish) followed by a name:\n", MAX_WAVES);

	waves = 0;
	memset(wave_people, 0, sizeof(wave_people));

	for (people = 0; people < MAX_PEOPLE; ++people) {
		rc = scanf("%u", &people_data[people].group);	// unsigned decimal
		if (0 == rc || EOF == rc || 0 == people_data[people].group)
			break;
		if (people_data[people].group < 0 || people_data[people].group > MAX_WAVES) {
			fprintf(stderr, C_ERROR "Invalid group id." C_NORMAL "\n");
			exit(EXIT_FAILURE);
		}
		// string limited to MAXLEN_NAME characters up to a new-line
		rc = scanf(" %" STR_VAL(MAXLEN_NAME) "[^\n]", people_data[people].name);

		rc = scanf("%1[\n]", &c);
		if (1 != rc && EOF != rc) {
			++shortened;
			// if the read of a long name was limited by MAXLEN_NAME, read everything up to \n
			rc = scanf("%*[^\n]");
		}

		if (waves < people_data[people].group)
			waves = people_data[people].group;	// set max wave
		// increase the number of people in this group
		++wave_people[ people_data[people].group - 1 ];
	}
	if (shortened)
		fprintf(stderr, C_ERROR "Warning: Name(s) shortened: %d" C_NORMAL "\n", shortened);
}

// sanity checks
void sanity_checks()
{
	int wave;
	if (waves < 1) {
		fprintf(stderr, C_ERROR "No groups defined." C_NORMAL "\n");
		exit(EXIT_FAILURE);
	}
	for (wave = 0; wave < waves; ++wave)
		if (wave_people[wave] < 1) {
			fprintf(stderr, C_ERROR "No people in group %d." C_NORMAL "\n", wave + 1);
			exit(EXIT_FAILURE);
		}
}

int main(int argc, char *argv[])
{
	pthread_t people_tids[MAX_PEOPLE];
	pthread_t nurse_tid;
	int people_ids[MAX_PEOPLE];
	int wave;
	int i;

	atexit(release_resources);	// release resources at exit

	// get the number of real positions from the argv[1] if given
	if (argc > 1) {
		positions = strtol(argv[1], NULL, 0);
		if (positions < 1 || positions > MAX_POSITIONS) {
			fprintf(stderr, C_ERROR "%d: Invalid number of positions (1 ≤ positions ≤ %d)." C_NORMAL "\n",
				positions, MAX_POSITIONS);
			return EXIT_FAILURE;
		}
	}

	// load people ids
	load_people();

	// check people data consistency
	sanity_checks();

	// print info
	printf("The number of people: " C_FREE "%d" C_NORMAL "\n", people);
	printf("The number of waves: " C_FREE "%d" C_NORMAL "\n", waves);
	printf("The number of free spots in the registration list: " C_FREE "%d" C_NORMAL "\n", positions);

	// print id

	// initialize resources

	// print list of people if they were not loaded from terminal
	if (!isatty(STDIN_FILENO))
		print_list("List of people to register", people_data, people);

	// create people threads
	for (i = 0; i < people; ++i) {
		people_ids[i] = i;	// id for each thread
		if (pthread_create(&people_tids[i], NULL, do_registration_and_vaccination, &people_ids[i])) {
			perror("pthread_create");
			return EXIT_FAILURE;
		}
	}

	// start vaccination thread
	if (pthread_create(&nurse_tid, NULL, nurse, NULL)) {
		perror("pthread_create");
		return EXIT_FAILURE;
	}

	// start waves of reservations
	for (wave = 0; wave < waves; ++wave) {
		printf("Starting all threads of wave " C_WAVE2 "%d" C_NORMAL ".\n", (wave + 1) % 2, wave + 1);
		pthread_mutex_lock(&sync_waves[wave].mutex);
			sync_waves[wave].started = true;
			pthread_cond_broadcast(&sync_waves[wave].cond);
		pthread_mutex_unlock(&sync_waves[wave].mutex);
		sleep(1);	// delay start of the next wave
	}

	// wait for all people threads
	for (i = 0; i < people; ++i)
		(void) pthread_join(people_tids[i], NULL);

	(void) pthread_join(nurse_tid, NULL);

	// system resources are released using atexit

	return EXIT_SUCCESS;
}

// EOF
