#include "mini_chess.h"

Bitboard bitboard_of_square(Square square) {
    return (Bitboard)1 << square;
}

Bitboard bitboard_of_file(File file) {
    return BB_FILE_A << file;
}

Bitboard bitboard_of_rank(Rank rank) {
    return BB_RANK_1 << (rank * FILE_NUM);
}
