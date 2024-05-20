CC = gcc -L. -O3 -Wall -Wextra

all: libsnake
	$(CC) src/main.c -o main -lsnake

generator: libsnake
	$(CC) src/generator.c -o generator -leuler -lsnake

libsnake: bitboard square
	ar -r libsnake.a bitboard.o square.o

bitboard:
	$(CC) -c lib/bitboard.c

square:
	$(CC) -c lib/square.c
