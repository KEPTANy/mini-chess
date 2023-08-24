#include "mini_chess.h"

#include <stdlib.h>

static char SQUARE_TO_STR[SQUARE_NUM][3];
static Square SQUARE_FLIP[SQUARE_NUM];

void square_init() {
    for (Square s = S_A1; s < SQUARE_NUM; s++) {
        SQUARE_TO_STR[s][0] = "abcde"[square_get_file(s)];
        SQUARE_TO_STR[s][1] = "123456"[square_get_rank(s)];
        SQUARE_TO_STR[s][2] = 0;
        SQUARE_FLIP[s] = square_create(square_get_file(s), RANK_NUM - square_get_rank(s));
    }
}

Square square_create(File file, Rank rank) {
    return rank * FILE_NUM + file;
}

File square_get_file(Square square) {
    return square % FILE_NUM;
}

Rank square_get_rank(Square square) {
    return square / FILE_NUM;
}

uint8_t square_distance(Square a, Square b) {
    File f = abs(square_get_file(a) - square_get_file(b));
    Rank r = abs(square_get_rank(a) - square_get_rank(b));
    return (f > r) ? f : r;
}

Square square_flip(Square s) {
    return SQUARE_FLIP[s];
}
