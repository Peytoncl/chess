#ifndef ENGINE_H
#define ENGINE_H

#include <stdint.h>

//extern uint64_t board;

enum PIECES
{
    WP_PIECE,
    WN_PIECE,
    WB_PIECE,
    WR_PIECE,
    WQ_PIECE,
    WK_PIECE,
    BP_PIECE,
    BN_PIECE,
    BB_PIECE,
    BR_PIECE,
    BQ_PIECE,
    BK_PIECE
};

extern uint64_t WP;
extern uint64_t WN;
extern uint64_t WB;
extern uint64_t WR;
extern uint64_t WQ;
extern uint64_t WK;

extern uint64_t BP;
extern uint64_t BN;
extern uint64_t BB;
extern uint64_t BR;
extern uint64_t BQ;
extern uint64_t BK;

extern uint64_t all_white(void);
extern uint64_t all_black(void);
extern uint64_t occupied(void);
extern uint64_t empty(void);
extern int check_square(int position);

#endif