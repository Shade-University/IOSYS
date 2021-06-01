// Operating Systems: sample code  (c) Tomáš Hudec
// Threads
// Critical Sections
//
// Example code that simulates two sequences of bank transactions in parallel.
// The critical section is the money transfer from one account to the other
// (there may be no money disappearing or suddenly appearing).
//
// Assignment:
// Solve the race condition using the POSIX semaphore.
// Replace the content of the synchronization function with the POSIX barrier.
//
// Zadání:
// Vyøešte problém soubìhu použitím posixového semaforu.
// Nahraïte obsah synchronizaèní funkce posixovou bariérou.

#define _XOPEN_SOURCE 600
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>




#define ACCOUNT 10000000
volatile int rich_guy = ACCOUNT;
volatile int poor_guy = 0;

time_t start_time;

// declaration of the semaphore and the barrier
sem_t semaphore;
pthread_barrier_t barrier;

// synchronize thread start
static void sync_start(void)
{
	int rc;
	rc = pthread_barrier_wait(&barrier);
	if (rc != 0 && rc != PTHREAD_BARRIER_SERIAL_THREAD){
		perror("pthread_ barrier_wait");
	}
}

bool transfer_money()
{
	int money;
	money = 1 + rand() % 10;
	if (money > rich_guy)
		money = rich_guy;
	//printf("($%d)\n", money);
	if (sem_wait(&semaphore) == -1){//když je hodnota menší než 0 blokujeme
		exit(EXIT_FAILURE);
	}

	rich_guy -= money;
	poor_guy += money;

	if (sem_post(&semaphore) == -1){
		exit(EXIT_FAILURE);
	}
	return (rich_guy <= 0 || poor_guy >= ACCOUNT);
}

void *bank_transaction(void *arg)
{
	bool done;

	sync_start();		// synchronize threads start / synchronizace startu vláken
	do {

		// do the money transfer
		done = transfer_money();

	} while (!done);

	return NULL;
}

int main(int argc, char *argv[])
{
	
	

	pthread_t transaction[2];
	int id0 = 0;
	int id1 = 1;

	start_time = time(NULL);
	srand(start_time + getpid());

	// id
	printf("Modifikaci provedl(a): st39700 Bauer David");

	
	printf("%s:\n  Simulation of concurrent bank transactions.\n", argv[0]);

	printf("Rich guy has $%d\n"
		"Poor guy has $%d\n"
		"Starting two parallel bank transfers...\n", rich_guy, poor_guy);

	// resource initialization
	if (sem_init(&semaphore, 0, 1) == -1){ // ošetøení chyby inicializace
		perror("Error");
		pthread_exit(NULL);
	}
	if (pthread_barrier_init(&barrier, NULL, 2)){
		perror("Error");
		pthread_exit(NULL);
	}
	pthread_create(&transaction[0], NULL, bank_transaction, &id0);
	pthread_create(&transaction[1], NULL, bank_transaction, &id1);

	puts("Waiting for transactions...");
	pthread_join(transaction[0], NULL);
	pthread_join(transaction[1], NULL);

	// release resources

	printf("Done.\n"
		"Rich guy has $%d\n"
		"Poor guy has $%d\n", rich_guy, poor_guy);

	if (rich_guy != 0 || poor_guy != ACCOUNT)
		printf("\nBAD TRANSACTIONS DETECTED!\n");
	return 0;
}
