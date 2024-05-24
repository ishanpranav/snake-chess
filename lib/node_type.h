// node_type.h
// Licensed under the MIT license.

// https://www.chessprogramming.org/Node_Types

/** */
enum NodeType
{
    NODE_TYPE_NONE = 0,
    NODE_TYPE_PRINCIPAL_VARIATION = 1,
    NODE_TYPE_CUT_BETA = 2,
    NODE_TYPE_ALL_ALPHA = 3
};

/** */
typedef enum NodeType NodeType;
