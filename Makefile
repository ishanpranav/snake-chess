# Makefile
# Copyright (c) 2024 Ishan Pranav
# Licensed under the MIT license.

CC = gcc -L. -O3 -Wall -Wextra

all: libsnake
	$(CC) src/main.c -o main -lsnake

generator: libsnake
	$(CC) src/generator.c -o generator -leuler -lsnake

libsnake: attack_table bitboard board castling_rights color piece square
	ar -r libsnake.a attack_table.o bitboard.o board.o castling_rights.o color.o piece.o square.o

attack_table:
	$(CC) -c lib/attack_table.c

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
