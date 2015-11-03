CC=gcc
CFLAGS=-c -Wall -std=c99

all: keylogger
	rm -f *.o

keylogger: keylogger.o
	$(CC) keylogger.o -o keylogger

keylogger.o: keylogger.c
	$(CC) $(CFLAGS) keylogger.c

clean:
	rm -f keylogger *.o
