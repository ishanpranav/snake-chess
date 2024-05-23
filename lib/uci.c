// uci.c
// Licensed under the MIT license.

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../ishan/euler.h"
#include "attack_table.h"
#include "board.h"
#include "uci.h"

static bool uci_evaluate_debug(Stream output, String value)
{
    return true;
}

static bool uci_evaluate_set_option(Stream output, String value)
{
    return true;
}

static bool uci_evaluate_new_game(Stream output)
{
    return true;
}

static bool uci_evaluate_position(Stream output, String value)
{
    return true;
}

static bool uci_evaluate_go_perft(Stream output, String value)
{
    value = strchr(value, ' ');

    if (!value)
    {
        return false;
    }

    int depth = atoi(value);
    AttackTable table = malloc(sizeof * table);
    struct Board state;

    attack_table(table);
    board_from_fen_string(&state, BOARD_INITIAL);
    board_write_string(stdout, &state, ENCODING_STANDARD);

    time_t start = time(NULL);
    long long result = perft(&state, table, depth);
    double elapsed = difftime(time(NULL), start);
    double speed = result / elapsed;

    printf(
        "elapsed: %lf s\n"
        "speed: %0.lf positions/s\n"
        "result: %lld positions\n",
        elapsed, speed, result);

    free(table);

    return true;
}

static bool uci_evaluate_go(Stream output, String value)
{
    String argument = NULL;

    if ((argument = strstr(value, "")))
    {

    }

    if ((argument = strstr(value, "perft")))
    {
        return uci_evaluate_go_perft(output, argument);
    }

    return true;
}

static bool uci_evaluate_stop(Stream output)
{
    return true;
}

static bool uci_evaluate_ponder_hit(Stream output)
{
    return true;
}

bool uci_evaluate(Stream output, String value)
{
    if (string_starts_with(value, "uci"))
    {
        fprintf(output,
            "id name snake-chess\n"
            "id author Ishan Pranav\n"
            "uciok\n");

        return true;
    }

    String command = NULL;

    if ((command = strstr(value, "debug")))
    {
        return uci_evaluate_debug(output, command);
    }

    if (string_starts_with(value, "isready"))
    {
        fprintf(output, "readyok\n");

        return true;
    }

    if ((command = strstr(value, "setoption")))
    {
        return uci_evaluate_set_option(output, command);
    }

    if (string_starts_with(value, "ucinewgame"))
    {
        return uci_evaluate_new_game(output);
    }

    if ((command = strstr(value, "position")))
    {
        return uci_evaluate_position(output, command);
    }

    if ((command = strstr(value, "go")))
    {
        return uci_evaluate_go(output, command);
    }

    if (string_starts_with(value, "stop"))
    {
        return uci_evaluate_stop(output);
    }

    if (string_starts_with(value, "ponderhit"))
    {
        return uci_evaluate_ponder_hit(output);
    }

    return !strstr(value, "quit");
}
