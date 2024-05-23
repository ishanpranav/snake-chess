// uci.c
// Licensed under the MIT license.

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../ishan/euler.h"
#include "move.h"
#include "perft.h"
#include "uci.h"

void uci(Uci instance, Stream output)
{
    board(&instance->board);
    attack_table(&instance->table);

    instance->output = output;
}

static bool uci_evaluate_debug(Uci instance, String value)
{
    return true;
}

static bool uci_evaluate_set_option(Uci instance, String value)
{
    return true;
}

static bool uci_evaluate_new_game(Uci instance)
{
    return true;
}

static bool uci_evaluate_position(Uci instance, String value)
{
    value = strchr(value, ' ') + 1;

    char *argument;

    if ((argument = strstr(value, "startpos")))
    {
        argument = strchr(argument, ' ') + 1;

        board_from_fen_string(&instance->board, BOARD_INITIAL);
    }

    if ((argument = strstr(value, "fen")))
    {
        argument = strchr(argument, ' ') + 1;

        board_from_fen_string(&instance->board, argument);
    }

    if ((argument = strstr(value, "moves")))
    {
        argument = strchr(argument, ' ') + 1;

        for (char *token = strtok(argument, " \n"); 
            token; 
            token = strtok(NULL, " \n"))
        {
            struct Move move;

            if (move_from_uci_string(
                    &move,
                    tok,
                    &instance->board,
                    &instance->table))
            {
                move_apply(&move, &instance->board);
            }
        }
    }

    return true;
}

static bool uci_evaluate_go_perft(Uci instance, String value)
{
    value = strchr(value, ' ') + 1;

    int depth = atoi(value);
    time_t start = time(NULL);
    long long result = perft(&instance->board, &instance->table, depth);
    double elapsed = difftime(time(NULL), start);
    double speed = result / elapsed;

    fprintf(instance->output,
            "info x-elapsed %lf s\n"
            "info x-speed %0.lf positions/s\n"
            "info x-result %lld positions\n",
            elapsed, speed, result);

    return true;
}

static bool uci_evaluate_go(Uci instance, String value)
{
    bool infinite = false;
    bool ponder = false;
    int depth = 0;
    int nodes = 0;
    int mate = 0;
    int moveTime = 0;
    int whiteTime = 0;
    int blackTime = 0;
    int whiteIncrement = 0;
    int blackIncrement = 0;
    int movesRemaining = 0;
    String argument = NULL;

    if ((argument = strstr(value, "perft")))
    {
        return uci_evaluate_go_perft(instance, argument);
    }

    if ((argument = strstr(value, "searchmoves")))
    {
    }

    if (strstr(value, "ponder"))
    {
        ponder = true;
    }

    if ((argument = strstr(value, "wtime")))
    {
        argument = strchr(argument, ' ') + 1;
        whiteTime = atoi(argument);
    }

    if ((argument = strstr(value, "btime")))
    {
        argument = strchr(argument, ' ') + 1;
        blackTime = atoi(argument);
    }

    if ((argument = strstr(value, "winc")))
    {
        argument = strchr(argument, ' ') + 1;
        whiteIncrement = atoi(argument);
    }

    if ((argument = strstr(value, "binc")))
    {
        argument = strchr(argument, ' ') + 1;
        blackIncrement = atoi(argument);
    }

    if ((argument = strstr(value, "movestogo")))
    {
        argument = strchr(argument, ' ') + 1;
        movesRemaining = atoi(argument);
    }

    if ((argument = strstr(value, "depth")))
    {
        argument = strchr(argument, ' ') + 1;
        depth = atoi(argument);
    }

    if ((argument = strstr(value, "nodes")))
    {
        argument = strchr(argument, ' ') + 1;
        nodes = atoi(argument);
    }

    if ((argument = strstr(value, "mate")))
    {
        argument = strchr(argument, ' ') + 1;
        mate = atoi(argument);
    }

    if ((argument = strstr(value, "movetime")))
    {
        argument = strchr(argument, ' ') + 1;
        moveTime = atoi(argument);
    }

    if (strstr(value, " infinite"))
    {
        infinite = true;
    }

    return true;
}

static bool uci_evaluate_stop(Uci instance)
{
    return true;
}

static bool uci_evaluate_ponder_hit(Uci instance)
{
    return true;
}

bool uci_evaluate(Uci instance, String value)
{
    if (strstr(value, "ucinewgame"))
    {
        return uci_evaluate_new_game(instance);
    }

    if (strstr(value, "uci"))
    {
        fprintf(instance->output,
                "id name snake-chess\n"
                "id author Ishan Pranav\n"
                "uciok\n");

        return true;
    }

    String command = NULL;

    if ((command = strstr(value, "debug")))
    {
        return uci_evaluate_debug(instance, command);
    }

    if (strstr(value, "isready"))
    {
        fprintf(instance->output, "readyok\n");

        return true;
    }

    if ((command = strstr(value, "setoption")))
    {
        return uci_evaluate_set_option(instance, command);
    }

    if ((command = strstr(value, "position")))
    {
        return uci_evaluate_position(instance, command);
    }

    if ((command = strstr(value, "go")))
    {
        return uci_evaluate_go(instance, command);
    }

    if (strstr(value, "stop"))
    {
        return uci_evaluate_stop(instance);
    }

    if (strstr(value, "ponderhit"))
    {
        return uci_evaluate_ponder_hit(instance);
    }

    if (strstr(value, "x-write"))
    {
        board_write_string(
            instance->output,
            &instance->board,
            ENCODING_STANDARD);

        return true;
    }

    return !strstr(value, "quit");
}
