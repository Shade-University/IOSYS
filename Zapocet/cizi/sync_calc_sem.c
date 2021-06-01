/*
* Zadání:
*
* Program musí vypsat správnì vypoètené hodnoty promìnných x, y a z,
* a to nezávisle na plánovacím poøadí vláken.
*
* Rùzná plánovací poøadí lze simulovat vkládáním pøíkazù sleep().
*
* Synchronizujte použitím posixového semaforu.
*
* Používejte vhodnì komentáøe.
*
* Modifikováno: 2015-01-05
*
*/

#include <stdio.h>	// printf 
#include <stdlib.h>	// exit 
#include <pthread.h>	// threads 
#include <errno.h>	// errno
#include <unistd.h>	// getopt

#include <semaphore.h>	//semaphore
// parametry sleep() pro simulaci rùzného plánovacího poøadí
int a = 0, b = 0, c = 0, d = 0;

// upovídanost programu
int verbosity = 0;

// sdílené promìnné a jejich výchozí hodnoty
volatile int x = 0, y = 0, z = 0;


// prototypy výpoèetních funkcí a výpisová funkce
int calc_x(int p);
int calc_y(int x);
int calc_z(int x, int y);
void print_xyz(int x, int y, int z);

// prototyp funkce pro vyhodnocení parametrù
void eval_params(int argc, char *argv[]);


// deklarace synchronizaèních promìnných

sem_t sync_sem;			// semafor pro synchronizaci ///////////////////////////////////////////////////////////////////
sem_t sync_sem_two;
#define _XOPEN_SOURCE 600
#define SEM_SYNC_INIT_VALUE	0	// 0, we are synchronizing

// výpoèetní vlákno 1, voláno z main() 
void func1(void)
{
	sleep(a);	// simulace další èinnosti èi zdržení plánovaèe

	// výpoèet x
	x = calc_x(1);
	sem_post(&sync_sem_two); //odblokuju vypocet Y

	sleep(c);	// simulace další èinnosti èi zdržení plánovaèe


	// výpoèet z je závislý na pøedcházejícím výpoètu x a y
	sem_wait(&sync_sem); //cekam na vypocet Y
	z = calc_z(x, y);
	sem_post(&sync_sem_two); // odblokuju výpis
	return;
}

// výpoèetní a výpisové vlákno 2, voláno z thread2() 
void func2(void)
{
	sleep(b);	// simulace další èinnosti èi zdržení plánovaèe


	// výpoèet y je závislý na pøedcházejícím výpoètu x
	sem_wait(&sync_sem_two); //cekam na vypocet X
	y = calc_y(x);
	sem_post(&sync_sem); // po výpoètu Y odblokuju výpoèet Z

	sleep(d);	// simulace další èinnosti èi zdržení plánovaèe


	// výpis: smí být provedeno až po výpoètu z
	sem_wait(&sync_sem_two); //cekam na Z
	print_xyz(x, y, z);

	return;
}


// druhé vlákno 
void *thread2(void *arg)
{
	func2();	// výpoèetní funkce 2
	return NULL;
}


int main(int argc, char *argv[])
{
	pthread_t thread2id;

	// výpis id
	printf("Modifikaci provedl(a): st39700 Bauer David");

	// vyhodnocení parametrù
	eval_params(argc, argv);

	// výpis hodnot èekání
	if (verbosity > 1)
		printf("Hodnoty èekání: %d, %d, %d, %d\n", a, b, c, d);

	// inicializace / alokace
	if (sem_init(&sync_sem, 0, SEM_SYNC_INIT_VALUE)) {
		perror("sem_init");
		exit(EXIT_FAILURE);
	}

	if (sem_init(&sync_sem_two, 0, SEM_SYNC_INIT_VALUE)) {
		perror("sem_init");
		exit(EXIT_FAILURE);
	}

	// vytvoøení druhého vlákna
	if (verbosity > 2)
		printf("Spouští se druhé vlákno.\n");
	if (pthread_create(&thread2id, NULL, thread2, NULL)) {
		perror("pthread_create");
		exit(EXIT_FAILURE);
	}

	// výpoèetní funkce 1
	func1();

	// èekání na dokonèení vlákna
	(void)pthread_join(thread2id, NULL);

	// dealokace 
	if (sem_destroy(&sync_sem)) {
		perror("sem_destroy");
		exit(EXIT_FAILURE);
	}

	return 0;
}


// dále nic není tøeba modifikovat


// výpoèetní funkce pro x
int calc_x(int p)
{
	int x;

	if (verbosity > 0)
		printf("Provádím výpoèet x.\n");
	x = p * p;
	if (verbosity > 1)
		printf("Vypoèteno: x = %d\n", x);
	return x;
}

// výpoèetní funkce pro y
int calc_y(int x)
{
	int y;

	if (verbosity > 0)
		printf("Provádím výpoèet y (pro x = %d).\n", x);
	y = x + 1;
	if (verbosity > 1)
		printf("Vypoèteno: y = %d\n", y);
	return y;
}

// výpoèetní funkce pro z
int calc_z(int x, int y)
{
	int z;

	if (verbosity > 0)
		printf("Provádím výpoèet z (pro x = %d, y = %d).\n", x, y);
	z = 2 * x + y - 1;
	if (verbosity > 1)
		printf("Vypoèteno: z = %d\n", z);
	return z;
}

// výpis promìnných
void print_xyz(int x, int y, int z)
{
	printf("x = %d, y = %d, z = %d\n", x, y, z);
}


// nápovìda
void usage(FILE *stream, char *self)
{
	fprintf(stream,
		"Užití:\n"
		"  %s -h\n"
		"  %s [-v|-q] [s1 [s2 [s3 [s4]]]]\n"
		"Úèel:\n"
		"  Simulace paralelních výpoètù a synchronizace.\n"
		"Pøepínaèe:\n"
		"  -h		nápovìda\n"
		"  -v		zvýšení upovídanosti programu (%d)\n"
		"  -q		snížení upovídanosti programu\n"
		"Parametry:\n"
		"  s1, s2, s3	doba èekání pøed výpoèty 1, 2 a 3 (%d, %d, %d)\n"
		"  s4		doba èekání pøed výpisem (%d)\n\n",
		self, self,
		verbosity,
		a, b, c,
		d);
}

// evaluace parametrù
void eval_params(int argc, char *argv[]) {
	int opt;

	opterr = 0;	// no error msg on unknown option, we care of this
	// evaluate options
	while ((opt = getopt(argc, argv, "hqv")) != -1) {
		switch (opt) {
			// -v -- inc verbosity
		case 'v':
			if (verbosity < 100)
				verbosity++;
			break;
			// -q -- dec verbosity
		case 'q':
			if (verbosity > 0)
				verbosity--;
			break;
			// -h -- print usage
		case 'h':
			usage(stdout, argv[0]);
			exit(EXIT_SUCCESS);
			// unknown option
		default:
			fprintf(stderr, "%c: unknown option.\n", optopt);
			usage(stderr, argv[0]);
			exit(2);
			break;
		}
	}

	// je-li zadán nìjaký argument, použije se jako hodnota pro sleep 
	if (argc > optind) {
		a = atoi(argv[optind]);
		if (argc > optind + 1) {
			b = atoi(argv[optind + 1]);
			if (argc > optind + 2) {
				c = atoi(argv[optind + 2]);
				if (argc > optind + 3) {
					d = atoi(argv[optind + 3]);
				}
			}
		}
	}

	return;
} // eval_params

// EOF
