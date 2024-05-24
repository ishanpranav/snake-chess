# Makefile
# Copyright (c) 2024 Ishan Pranav
# Licensed under the MIT license.

CC = gcc -L. -march=native -O3 -Wall -Wextra

all: libsnake
	$(CC) src/main.c -o main -lsnake

libsnake: attack_provider search
	$(CC) -c lib/*.c
	ar -r libsnake.a *.o

attack_provider:
	$(CC) -c lib/attack_providers/*.c

search:
	$(CC) -c lib/searches/*.c
