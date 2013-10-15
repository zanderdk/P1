CC=gcc
CFLAGS=-Wall

main: primes.o Gopgave1.o
	$(CC) $(CFLAGS) Gopgave1.o primes.o -o Gopgave1
	rm -r -f *.o

primes.o: primes.c
	$(CC) $(CFLAGS) -lm -c primes.c

Gopgave1.o: Gopgave1.c primes.h
	$(CC) $(CFLAGS) -c Gopgave1.c