// uci.c
// Licensed under the MIT license.

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../ishan/euler.h"
#include "evaluation.h"
#include "perft.h"
#include "search.h"
#include "uci.h"

void uci(Uci instance, Stream output)
{
    uint32_t state = ZOBRIST_SEED;

    board(&instance->board);
    attack_table(&instance->table);
    zobrist(&instance->zobrist, &state);

    instance->output = output;
    instance->started = false;
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
    board_from_fen_string(&instance->board, BOARD_INITIAL, &instance->zobrist);
    
    return true;
}

static bool uci_evaluate_position(Uci instance, String value)
{
    value = strchr(value, ' ') + 1;

    euler_assert(value - 1);

    char *argument;
    Board board = &instance->board;

    if (strstr(value, "startpos"))
    {
        board_from_fen_string(board, BOARD_INITIAL, &instance->zobrist);
    }

    if ((argument = strstr(value, "fen")))
    {
        argument = strchr(argument, ' ') + 1;

        euler_assert(argument - 1);
        board_from_fen_string(board, argument, &instance->zobrist);
    }

    if ((argument = strstr(value, "moves")))
    {
        argument = strchr(argument, ' ') + 1;

        euler_assert(argument - 1);

        for (char *token = strtok(argument, " \n");
             token;
             token = strtok(NULL, " \n"))
        {
            struct Move move;

            if (move_from_uci_string(&move, token, board, &instance->table))
            {
                move_apply(&move, board, &instance->zobrist);
            }
        }
    }

    return true;
}

static bool uci_evaluate_go(Uci instance, String value)
{
    int depth = 5;
    int nodes = 0;
    int mate = 0;
    int moveTime = 0;
    int whiteTime = 0;
    int blackTime = 0;
    int whiteIncrement = 0;
    int blackIncrement = 0;
    int movesRemaining = 0;
    bool ponder = false;
    bool infinite = false;
    String argument = NULL;
    Board board = &instance->board;
    AttackTable table = &instance->table;

    if ((argument = strstr(value, "perft")))
    {
        argument = strchr(argument, ' ') + 1;

        euler_assert(argument - 1);

        depth = atoi(argument);

        time_t start = time(NULL);
        long long result = perft(board, table, depth);
        double elapsed = difftime(time(NULL), start);
        double speed = result / elapsed;

        fprintf(instance->output,
                "info .elapsed %lf s\n"
                "info .speed %0.lf positions/s\n"
                "info .result %lld positions\n",
                elapsed, speed, result);

        return true;
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

        euler_assert(argument - 1);

        whiteTime = atoi(argument);
    }

    if ((argument = strstr(value, "btime")))
    {
        argument = strchr(argument, ' ') + 1;

        euler_assert(argument - 1);

        blackTime = atoi(argument);
    }

    if ((argument = strstr(value, "winc")))
    {
        argument = strchr(argument, ' ') + 1;

        euler_assert(argument - 1);

        whiteIncrement = atoi(argument);
    }

    if ((argument = strstr(value, "binc")))
    {
        argument = strchr(argument, ' ') + 1;

        euler_assert(argument - 1);

        blackIncrement = atoi(argument);
    }

    if ((argument = strstr(value, "movestogo")))
    {
        argument = strchr(argument, ' ') + 1;

        euler_assert(argument - 1);

        movesRemaining = atoi(argument);
    }

    if ((argument = strstr(value, "depth")))
    {
        argument = strchr(argument, ' ') + 1;

        euler_assert(argument - 1);

        depth = atoi(argument);
    }

    if ((argument = strstr(value, "nodes")))
    {
        argument = strchr(argument, ' ') + 1;

        euler_assert(argument - 1);

        nodes = atoi(argument);
    }

    if ((argument = strstr(value, "mate")))
    {
        argument = strchr(argument, ' ') + 1;

        euler_assert(argument - 1);

        mate = atoi(argument);
    }

    if ((argument = strstr(value, "movetime")))
    {
        argument = strchr(argument, ' ') + 1;

        euler_assert(argument - 1);

        moveTime = atoi(argument);
    }

    if (strstr(value, "infinite"))
    {
        infinite = true;
    }

    euler_assert(depth > 0);

    instance->started = true;

    char buffer[8] = {0};
    struct Move bestMove;

    fprintf(instance->output,
            "info depth %d\n"
            "info score cp %d\n",
            depth,
            evaluation(board));
    negamax_search(&bestMove, board, table, &instance->zobrist, depth);
    move_write_uci_string(buffer, &bestMove);
    fprintf(instance->output, "bestmove %s\n", buffer);

    instance->started = false;

    return true;
}

static bool uci_evaluate_stop(Uci instance)
{
    instance->started = false;

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

    return !strstr(value, "quit");
}
