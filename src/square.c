#include "mini_chess.h"

Square square_create(File file, Rank rank) {
    return rank * FILE_NUM + file;
}

File square_get_file(Square square) {
    return square % FILE_NUM;
}

Rank square_get_rank(Square square) {
    return square / FILE_NUM;
}
