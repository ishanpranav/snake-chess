CC		= gcc
CFLAGS	= -g -Wall
EXT		= .exe

all: \
	program

attacks: src/attacks.c
	$(CC) $(CFLAGS) -c src/$@.c -o obj/$@.o

bitboard: src/bitboard.c
	$(CC) $(CFLAGS) -c src/$@.c -o obj/$@.o

program: \
	attacks \
	bitboard \
	src/program.c

	$(CC) $(CFLAGS) src/$@.c obj/attacks.o obj/bitboard.o -o bin/$@$(EXT)

clean:
	rm -f *~ obj/* bin/* *.gch core a.out
