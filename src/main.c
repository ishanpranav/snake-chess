// main.c
// Licensed under the MIT license.

#include <stdlib.h>
#include <string.h>
#include "../lib/uci.h"

int main(void)
{
    Uci state = malloc(sizeof * state);

    euler_assert(state);
    uci(state, stdout);
    
    char buffer[16384];

    while (fgets(buffer, sizeof buffer, stdin) && uci_evaluate(state, buffer))
    {
    }

    free(state);

    return 0;
}
