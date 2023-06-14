#include "mini_chess.h"

#include <stdlib.h>

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
