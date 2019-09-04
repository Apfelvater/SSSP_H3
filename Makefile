CFLAGS=-std=c11 -Wall -pedantic -g -fopenmp
LDFLAGS=-fopenmp
CC=gcc

all: library

.PHONY: all clean

library: md5.o library.o
	$(CC) $(LDFLAGS) -o library md5.o library.o armon/libart/src/art.c

library.o: library.c md5.h

trivial: md5.o library_wordlist.o
	$(CC) $(LDFLAGS) -o library_wordlist md5.o library_wordlist.o

library_wordlist.o: library_wordlist.c md5.h

clean:
	rm -f library
	rm -f library.o library.o md5.o
	rm -f library_wordlist
	rm -f library_wordlist.o

