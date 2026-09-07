#include "../headers/engine.h"

// bitboard //

// piece starting position

uint64_t WP = 0x000000000000FF00ULL;
uint64_t WN = 0x0000000000000042ULL;
uint64_t WB = 0x0000000000000024ULL;
uint64_t WR = 0x0000000000000081ULL;
uint64_t WQ = 0x0000000000000008ULL;
uint64_t WK = 0x0000000000000010ULL;

uint64_t BP = 0x00FF000000000000ULL;
uint64_t BN = 0x4200000000000000ULL;
uint64_t BB = 0x2400000000000000ULL;
uint64_t BR = 0x8100000000000000ULL;
uint64_t BQ = 0x0800000000000000ULL;
uint64_t BK = 0x1000000000000000ULL;

uint64_t all_white(void) { return WP | WN | WB | WR | WQ | WK; } // all white pieces

uint64_t all_black(void) { return BP | BN | BB | BR | BQ | BK; } // all black pieces

uint64_t occupied(void) { return all_white() | all_black(); } // all occupied spaces

uint64_t empty(void) { return ~occupied(); } // all empty spaces

int check_square(int position) // return integer based on piece enum
{
    if (occupied() & (1 << position)) // position is occupied
    {
        if (all_white() & (1 << position)) // position is white
        {
            if (WP & (1 << position)) return 0;
            if (WN & (1 << position)) return 1;
            if (WB & (1 << position)) return 2;
            if (WR & (1 << position)) return 3;
            if (WQ & (1 << position)) return 4;
            if (WK & (1 << position)) return 5;
        }

        if (all_black() & (1 << position)) // position is black
        {
            if (BP & (1 << position)) return 6;
            if (BN & (1 << position)) return 7;
            if (BB & (1 << position)) return 8;
            if (BR & (1 << position)) return 9;
            if (BQ & (1 << position)) return 10;
            if (BK & (1 << position)) return 11;
        }
    }
    else return -1;
}