// sliding.c
// Licensed under the MIT license.

#include "bitboard.h"
#include "file.h"
#include "rank.h"
#include "sliding.h"

uint64_t sliding_generate_bishop_relevant_occupancies(Square square)
{
    uint64_t result = 0;
    Rank targetRank = square / 8;
    File targetFile = square % 8;
    int rank = targetRank + 1;
    int file = targetFile + 1;

    while (rank <= RANK_SEVENTH && file <= FILE_G)
    {
        result |= bitboard(rank * 8 + file);
        rank++;
        file++;
    }

    rank = targetRank - 1;
    file = targetFile + 1;

    while (rank >= RANK_SECOND && file <= FILE_G)
    {
        result |= bitboard(rank * 8 + file);
        rank--;
        file++;
    }

    rank = targetRank + 1;
    file = targetFile - 1;

    while (rank <= RANK_SEVENTH && file >= FILE_B)
    {
        result |= bitboard(rank * 8 + file);
        rank++;
        file--;
    }

    rank = targetRank - 1;
    file = targetFile - 1;

    while (rank >= RANK_SECOND && file >= FILE_B)
    {
        result |= bitboard(rank * 8 + file);
        rank--;
        file--;
    }

    return result;
}

uint64_t sliding_generate_rook_relevant_occupancies(Square square)
{
    uint64_t result = 0;
    Rank targetRank = square / 8;
    File targetFile = square % 8;

    for (Rank rank = targetRank + 1; rank <= RANK_SEVENTH; rank++)
    {
        result |= bitboard(rank * 8 + targetFile);
    }

    for (int rank = targetRank - 1; rank >= RANK_SECOND; rank--)
    {
        result |= bitboard(rank * 8 + targetFile);
    }

    for (File file = targetFile + 1; file <= FILE_G; file++)
    {
        result |= bitboard(targetRank * 8 + file);
    }

    for (int file = targetFile - 1; file >= FILE_B; file--)
    {
        result |= bitboard(targetRank * 8 + file);
    }

    return result;
}

uint64_t sliding_generate_bishop_attacks(Square square, uint64_t obstacles)
{
    uint64_t result = 0;
    Rank targetRank = square / 8;
    File targetFile = square % 8;
    int rank = targetRank + 1;
    int file = targetFile + 1;

    while (rank < RANKS && file < FILES)
    {
        uint64_t target = bitboard(rank * 8 + file);

        result |= target;

        if (target & obstacles)
        {
            break;
        }

        rank++;
        file++;
    }

    rank = targetRank - 1;
    file = targetFile + 1;

    while (rank >= 0 && file < FILES)
    {
        uint64_t target = bitboard(rank * 8 + file);

        result |= target;

        if (target & obstacles)
        {
            break;
        }

        rank--;
        file++;
    }

    rank = targetRank + 1;
    file = targetFile - 1;

    while (rank < RANKS && file >= 0)
    {
        uint64_t target = bitboard(rank * 8 + file);

        result |= target;

        if (target & obstacles)
        {
            break;
        }

        rank++;
        file--;
    }

    rank = targetRank - 1;
    file = targetFile - 1;

    while (rank >= 0 && file >= 0)
    {
        uint64_t target = bitboard(rank * 8 + file);

        result |= target;

        if (target & obstacles)
        {
            break;
        }

        rank--;
        file--;
    }

    return result;
}

uint64_t sliding_generate_rook_attacks(Square square, uint64_t obstacles)
{
    uint64_t result = 0;
    Rank targetRank = square / 8;
    File targetFile = square % 8;

    for (Rank rank = targetRank + 1; rank < RANKS; rank++)
    {
        uint64_t target = bitboard(rank * 8 + targetFile);

        result |= target;

        if (target & obstacles)
        {
            break;
        }
    }

    for (int rank = targetRank - 1; rank >= 0; rank--)
    {
        uint64_t target = bitboard(rank * 8 + targetFile);

        result |= target;

        if (target & obstacles)
        {
            break;
        }
    }

    for (File file = targetFile + 1; file < FILES; file++)
    {
        uint64_t target = bitboard(targetRank * 8 + file);

        result |= target;

        if (target & obstacles)
        {
            break;
        }
    }

    for (int file = targetFile - 1; file >= 0; file--)
    {
        uint64_t target = bitboard(targetRank * 8 + file);

        result |= target;

        if (target & obstacles)
        {
            break;
        }
    }

    return result;
}
