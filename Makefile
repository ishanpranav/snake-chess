CC = gcc -O3 -Wall -Wextra

all: bitboard
	$(CC) src/main.c bitboard.o -o main

generator: bitboard
	$(CC) src/generator.c bitboard.o -o generator

bitboard:
	$(CC) -c lib/bitboard.c
