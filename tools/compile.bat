:: compile.bat
:: Copyright (c) 2024 Ishan Pranav
:: Licensed under the MIT license.

Del *.o
clang -march=native -O3 -c lib/*.c lib/attack_providers/*.c
clang -march=native -D ENCODING_STANDARD=ENCODING_ASCII -O3 src/snake_perft.c *.o -o snake_perft.exe
