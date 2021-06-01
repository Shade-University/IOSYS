# Vlastní Makefile
CC = gcc
CFLAGS = -Wall -D_REENTRANT
LDLIBS = -lpthread -lrt

RM = /bin/rm -f

OBJECTS = *.o
BACKUPS = *~ *.bak
PROGRAMS = bank_transactions_sem_barrier sync_calc_sem
INDIVIDUALLY = 

all: $(PROGRAMS)

solo: $(INDIVIDUALLY)

bank_transactions_sem_barrier: bank_transactions_sem_barrier.c
	$(CC) $(CFLAGS) bank_transactions_sem_barrier.c -o bank_transactions_sem_barrier $(LDLIBS)

sync_calc_sem: sync_calc_sem.c
	$(CC) $(CFLAGS) sync_calc_sem.c -o sync_calc_sem $(LDLIBS)

clean:
	$(RM) $(OBJECTS) $(BACKUPS) $(PROGRAMS) $(INDIVIDUALLY)