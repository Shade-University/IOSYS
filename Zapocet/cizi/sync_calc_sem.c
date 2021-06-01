/*
* Zad�n�:
*
* Program mus� vypsat spr�vn� vypo�ten� hodnoty prom�nn�ch x, y a z,
* a to nez�visle na pl�novac�m po�ad� vl�ken.
*
* R�zn� pl�novac� po�ad� lze simulovat vkl�d�n�m p��kaz� sleep().
*
* Synchronizujte pou�it�m posixov�ho semaforu.
*
* Pou��vejte vhodn� koment��e.
*
* Modifikov�no: 2015-01-05
*
*/

#include <stdio.h>	// printf 
#include <stdlib.h>	// exit 
#include <pthread.h>	// threads 
#include <errno.h>	// errno
#include <unistd.h>	// getopt

#include <semaphore.h>	//semaphore
// parametry sleep() pro simulaci r�zn�ho pl�novac�ho po�ad�
int a = 0, b = 0, c = 0, d = 0;

// upov�danost programu
int verbosity = 0;

// sd�len� prom�nn� a jejich v�choz� hodnoty
volatile int x = 0, y = 0, z = 0;


// prototypy v�po�etn�ch funkc� a v�pisov� funkce
int calc_x(int p);
int calc_y(int x);
int calc_z(int x, int y);
void print_xyz(int x, int y, int z);

// prototyp funkce pro vyhodnocen� parametr�
void eval_params(int argc, char *argv[]);


// deklarace synchroniza�n�ch prom�nn�ch

sem_t sync_sem;			// semafor pro synchronizaci ///////////////////////////////////////////////////////////////////
sem_t sync_sem_two;
#define _XOPEN_SOURCE 600
#define SEM_SYNC_INIT_VALUE	0	// 0, we are synchronizing

// v�po�etn� vl�kno 1, vol�no z main() 
void func1(void)
{
	sleep(a);	// simulace dal�� �innosti �i zdr�en� pl�nova�e

	// v�po�et x
	x = calc_x(1);
	sem_post(&sync_sem_two); //odblokuju vypocet Y

	sleep(c);	// simulace dal�� �innosti �i zdr�en� pl�nova�e


	// v�po�et z je z�visl� na p�edch�zej�c�m v�po�tu x a y
	sem_wait(&sync_sem); //cekam na vypocet Y
	z = calc_z(x, y);
	sem_post(&sync_sem_two); // odblokuju v�pis
	return;
}

// v�po�etn� a v�pisov� vl�kno 2, vol�no z thread2() 
void func2(void)
{
	sleep(b);	// simulace dal�� �innosti �i zdr�en� pl�nova�e


	// v�po�et y je z�visl� na p�edch�zej�c�m v�po�tu x
	sem_wait(&sync_sem_two); //cekam na vypocet X
	y = calc_y(x);
	sem_post(&sync_sem); // po v�po�tu Y odblokuju v�po�et Z

	sleep(d);	// simulace dal�� �innosti �i zdr�en� pl�nova�e


	// v�pis: sm� b�t provedeno a� po v�po�tu z
	sem_wait(&sync_sem_two); //cekam na Z
	print_xyz(x, y, z);

	return;
}


// druh� vl�kno 
void *thread2(void *arg)
{
	func2();	// v�po�etn� funkce 2
	return NULL;
}


int main(int argc, char *argv[])
{
	pthread_t thread2id;

	// v�pis id
	printf("Modifikaci provedl(a): st39700 Bauer David");

	// vyhodnocen� parametr�
	eval_params(argc, argv);

	// v�pis hodnot �ek�n�
	if (verbosity > 1)
		printf("Hodnoty �ek�n�: %d, %d, %d, %d\n", a, b, c, d);

	// inicializace / alokace
	if (sem_init(&sync_sem, 0, SEM_SYNC_INIT_VALUE)) {
		perror("sem_init");
		exit(EXIT_FAILURE);
	}

	if (sem_init(&sync_sem_two, 0, SEM_SYNC_INIT_VALUE)) {
		perror("sem_init");
		exit(EXIT_FAILURE);
	}

	// vytvo�en� druh�ho vl�kna
	if (verbosity > 2)
		printf("Spou�t� se druh� vl�kno.\n");
	if (pthread_create(&thread2id, NULL, thread2, NULL)) {
		perror("pthread_create");
		exit(EXIT_FAILURE);
	}

	// v�po�etn� funkce 1
	func1();

	// �ek�n� na dokon�en� vl�kna
	(void)pthread_join(thread2id, NULL);

	// dealokace 
	if (sem_destroy(&sync_sem)) {
		perror("sem_destroy");
		exit(EXIT_FAILURE);
	}

	return 0;
}


// d�le nic nen� t�eba modifikovat


// v�po�etn� funkce pro x
int calc_x(int p)
{
	int x;

	if (verbosity > 0)
		printf("Prov�d�m v�po�et x.\n");
	x = p * p;
	if (verbosity > 1)
		printf("Vypo�teno: x = %d\n", x);
	return x;
}

// v�po�etn� funkce pro y
int calc_y(int x)
{
	int y;

	if (verbosity > 0)
		printf("Prov�d�m v�po�et y (pro x = %d).\n", x);
	y = x + 1;
	if (verbosity > 1)
		printf("Vypo�teno: y = %d\n", y);
	return y;
}

// v�po�etn� funkce pro z
int calc_z(int x, int y)
{
	int z;

	if (verbosity > 0)
		printf("Prov�d�m v�po�et z (pro x = %d, y = %d).\n", x, y);
	z = 2 * x + y - 1;
	if (verbosity > 1)
		printf("Vypo�teno: z = %d\n", z);
	return z;
}

// v�pis prom�nn�ch
void print_xyz(int x, int y, int z)
{
	printf("x = %d, y = %d, z = %d\n", x, y, z);
}


// n�pov�da
void usage(FILE *stream, char *self)
{
	fprintf(stream,
		"U�it�:\n"
		"  %s -h\n"
		"  %s [-v|-q] [s1 [s2 [s3 [s4]]]]\n"
		"��el:\n"
		"  Simulace paraleln�ch v�po�t� a synchronizace.\n"
		"P�ep�na�e:\n"
		"  -h		n�pov�da\n"
		"  -v		zv��en� upov�danosti programu (%d)\n"
		"  -q		sn�en� upov�danosti programu\n"
		"Parametry:\n"
		"  s1, s2, s3	doba �ek�n� p�ed v�po�ty 1, 2 a 3 (%d, %d, %d)\n"
		"  s4		doba �ek�n� p�ed v�pisem (%d)\n\n",
		self, self,
		verbosity,
		a, b, c,
		d);
}

// evaluace parametr�
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

	// je-li zad�n n�jak� argument, pou�ije se jako hodnota pro sleep 
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
