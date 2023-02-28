CC		= gcc
CFLAGS	= -g -Wall
EXT		= .exe

all: \
	program

attack_table: src/attack_table.c
	$(CC) $(CFLAGS) -c src/$@.c -o obj/$@.o

bitboard: src/bitboard.c
	$(CC) $(CFLAGS) -c src/$@.c -o obj/$@.o

program: \
	attack_table \
	bitboard \
	src/program.c

	$(CC) $(CFLAGS) src/$@.c obj/attack_table.o obj/bitboard.o -o bin/$@$(EXT)

clean:
	rm -f *~ obj/* bin/* *.gch core a.out
