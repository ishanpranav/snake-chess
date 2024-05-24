// transposition.h
// Licensed under the MIT license.

// https://www.chessprogramming.org/Transposition_Table

#include <stdint.h>
#include "move.h"
#include "node_type.h"

/** */
struct Transposition
{
    uint64_t hash;
    enum NodeType type;
    int depth;
    int score;
    struct Move value;
};

/** */
typedef struct Transposition* Transposition;
