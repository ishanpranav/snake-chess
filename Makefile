# Makefile
# Copyright (c) 2024 Ishan Pranav
# Licensed under the MIT license.

CC = gcc -L. -O3 -Wall -Wextra

all: libsnake snake_perft
	$(CC) src/main.c -o main -lsnake

snake_perft: libsnake
	$(CC) src/snake_perft.c -o snake_perft -lsnake

libsnake: attack_provider attack_table bitboard bitboard_iterator board \
	castling_rights check color move perft piece spawn square
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

check:
	$(CC) -c lib/check.c

color:
	$(CC) -c lib/color.c

move:
	$(CC) -c lib/move.c

perft:
	$(CC) -c lib/perft.c

piece:
	$(CC) -c lib/piece.c

spawn:
	$(CC) -c lib/spawn.c

square:
	$(CC) -c lib/square.c
