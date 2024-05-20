CC = gcc -L. -O3 -Wall -Wextra

all: libsnake
	$(CC) src/main.c -o main -lsnake

generator: libsnake
	$(CC) src/generator.c -o generator -leuler -lsnake

libsnake: bitboard board castling_rights color piece square
	ar -r libsnake.a bitboard.o board.o castling_rights.o color.o piece.o square.o

bitboard:
	$(CC) -c lib/bitboard.c

board:
	$(CC) -c lib/board.c

castling_rights:
	$(CC) -c lib/castling_rights.c

color:
	$(CC) -c lib/color.c

piece:
	$(CC) -c lib/piece.c

square:
	$(CC) -c lib/square.c
