CC = gcc -L. -O3 -Wall -Wextra

all: bitboard square
	$(CC) src/main.c bitboard.o square.o -o main

generator: bitboard square libeuler
	$(CC) src/generator.c bitboard.o square.o -o generator -leuler

libeuler: xorshift32_random
	ar -r libeuler.a xorshift32_random.o

bitboard:
	$(CC) -c lib/bitboard.c

magic:
	$(CC) -c lib/magic.c
	
square:
	$(CC) -c lib/square.c

xorshift32_random: \
	ishan/randoms/xorshift32_random.c \
	ishan/random.h \
	ishan/object.h
	$(CC) -c ishan/randoms/xorshift32_random.c
