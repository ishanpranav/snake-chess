// transposition.h
// Licensed under the MIT license.

// https://www.chessprogramming.org/Transposition_Table

#include <stdint.h>
#include "node_type.h"

/** */
struct Transposition
{
    uint64_t hash;
    enum NodeType type;
    int depth;
    int score;
};

/** */
typedef struct Transposition* Transposition;