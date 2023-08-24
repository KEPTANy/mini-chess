#include "mini_chess.h"

#include <stdlib.h>

PVLine pv_line;

void movelist_push(MoveList *list, Move move) {
    list->list[list->size++] = move;
}

void movelist_pop(MoveList *list) {
    list->size--;
}

static const Score MVV_LVA[PIECE_TYPE_NUM][PIECE_TYPE_NUM] = {
    16, 26, 36, 46, 56, 66,
    15, 25, 35, 45, 55, 65,
    14, 24, 34, 44, 54, 64,
    13, 23, 33, 43, 53, 63,
    12, 22, 32, 42, 52, 62,
    11, 21, 31, 41, 51, 61
};

static int score_move(Move move) {
    if (move_is_capture(move))
        return MVV_LVA[piece_get_type(move_get_moving_piece(move))][piece_get_type(move_get_captured_piece(move))];
    return 0;
}

static int cmp(const void *m1, const void *m2) {
    return score_move(*((Move *)m2)) - score_move(*((Move *)m1));
}

void movelist_sort(MoveList *list) {
    qsort(list->list, list->size, sizeof(Move), cmp);
}
