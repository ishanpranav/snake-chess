CC = gcc -O3 -Wall -Wextra

all: bitboard square
	$(CC) src/main.c bitboard.o square.o -o main

generator: bitboard square
	$(CC) src/generator.c bitboard.o square.o -o generator

bitboard:
	$(CC) -c lib/bitboard.c

square:
	$(CC) -c lib/square.c
