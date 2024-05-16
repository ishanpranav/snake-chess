CC = gcc -O3 -Wall -Wextra

all: bitboard
	$(CC) src/main.c bitboard.o -o main

bitboard:
	$(CC) -c lib/bitboard.c
