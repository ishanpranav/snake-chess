# Makefile
# Copyright (c) 2024 Ishan Pranav
# Licensed under the MIT license.

CC = gcc -L. -march=native -O3 -Wall -Wextra

all: libsnake
	$(CC) src/main.c -o main -lsnake

libsnake: attack_provider attack_table bitboard bitboard_iterator board \
	castling_rights check color evaluation move move_collection perft piece \
	search spawn square	uci ishan_string
	ar -r libsnake.a *.o

attack_provider:
	$(CC) -c lib/attack_providers/*.c

search:
	$(CC) -c lib/searches/*.c

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

evaluation:
	$(CC) -c lib/evaluation.c

move:
	$(CC) -c lib/move.c

move_collection:
	$(CC) -c lib/move_collection.c

perft:
	$(CC) -c lib/perft.c

piece:
	$(CC) -c lib/piece.c

spawn:
	$(CC) -c lib/spawn.c

square:
	$(CC) -c lib/square.c

uci:
	$(CC) -c lib/uci.c

ishan_string:
	$(CC) -c ishan/string.c
