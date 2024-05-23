// uci.h
// Licensed under the MIT license.

#include "../ishan/euler.h"
#include "../ishan/stream.h"
#include "attack_table.h"
#include "board.h"

/** */
struct Uci
{
    struct Board board;
    struct AttackTable table;
    FILE* output;
};

/** */
typedef struct Uci* Uci;

/**
 * 
 * @param instance
 * @param output
*/
void uci(Uci instance, Stream output);

/**
 *
 * @param output
 * @param value
 * @return
*/
bool uci_evaluate(Uci instance, String value);
