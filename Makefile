# Makefile
# Copyright (c) 2024 Ishan Pranav
# Licensed under the MIT license.

CC = gcc -L. -O3 -Wall -Wextra

all: libsnake generator
	$(CC) src/main.c -o main -lsnake

generator: libsnake
	$(CC) src/generator.c -o generator -leuler -lsnake

libsnake: attack_provider attack_table bitboard bitboard_iterator board \
	castling_rights color piece square list
	ar -r libsnake.a *.o

attack_provider:
	$(CC) -c lib/attack_providers/*.c

attack_table:
	$(CC) -c lib/attack_table.c

bitboard:
	$(CC) -c lib/bitboard.c

bitboard_iterator:
	$(CC) -c lib/bitboard_iterator.c

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

list:
	$(CC) -c ishan/list.c
