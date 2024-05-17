CC = gcc -L. -O3 -Wall -Wextra

all: libsnake
	$(CC) src/main.c -o main -lsnake

generator: libeuler libsnake
	$(CC) src/generator.c -o generator -leuler -lsnake

magic: libeuler libsnake
	$(CC) src/magic.c -o magic -leuler -lsnake
	
libeuler: xorshift32_random
	ar -r libeuler.a xorshift32_random.o

libsnake: bitboard sliding square
	ar -r libsnake.a bitboard.o sliding.o square.o

bitboard:
	$(CC) -c lib/bitboard.c

sliding:
	$(CC) -c lib/sliding.c

square:
	$(CC) -c lib/square.c

xorshift32_random: \
	ishan/randoms/xorshift32_random.c \
	ishan/random.h \
	ishan/object.h
	$(CC) -c ishan/randoms/xorshift32_random.c
