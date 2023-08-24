#include "mini_chess.h"

static Bitboard ATTACKS_PAWN[COLOR_NUM][SQUARE_NUM];
static Bitboard ATTACKS_KNIGHT[SQUARE_NUM];
static Bitboard ATTACKS_KING[SQUARE_NUM];

void attacks_init() {
    for (Square sqr = S_A1; sqr < SQUARE_NUM; sqr++) {
        Bitboard bb = bitboard_of_square(sqr);

        ATTACKS_PAWN[C_WHITE][sqr] = attacks_pawns(bb, C_WHITE);
        ATTACKS_PAWN[C_BLACK][sqr] = attacks_pawns(bb, C_BLACK);

        ATTACKS_KNIGHT[sqr] = attacks_knights(bb);

        ATTACKS_KING[sqr] = attacks_kings(bb);
    }
}

Bitboard attacks_pawn(Square square, Color color) {
    return ATTACKS_PAWN[color][square];
}

Bitboard attacks_knight(Square square) {
    return ATTACKS_KNIGHT[square];
}

Bitboard attacks_bishop(Square square, Bitboard occupied) {
    Bitboard res = 0;
    static const Direction dirs[] = { D_NE, D_SE, D_SW, D_NW };
    for (int i = 0; i < ARRAY_SIZE(dirs); i++) {
        for (Square curr = square + dirs[i];
             curr < SQUARE_NUM && square_distance(curr, curr - dirs[i]) == 1;
             curr += dirs[i]) {

            res |= bitboard_of_square(curr);
            if (occupied & bitboard_of_square(curr))
                break;
        }
    }
    return BB_ALL_SQUARES & res;
}

Bitboard attacks_rook(Square square, Bitboard occupied) {
    Bitboard res = 0;
    static const Direction dirs[] = { D_N, D_S, D_E, D_W };
    for (int i = 0; i < ARRAY_SIZE(dirs); i++) {
        for (Square curr = square + dirs[i];
             curr < SQUARE_NUM && square_distance(curr, curr - dirs[i]) == 1;
             curr += dirs[i]) {

            res |= bitboard_of_square(curr);
            if (occupied & bitboard_of_square(curr))
                break;
        }
    }
    return BB_ALL_SQUARES & res;
}

Bitboard attacks_queen(Square square, Bitboard occupied) {
    return attacks_bishop(square, occupied) | attacks_rook(square, occupied);
}

Bitboard attacks_king(Square square) {
    return ATTACKS_KING[square];
}

Bitboard attacks_pawns(Bitboard pawns, Color color) {
    return BB_ALL_SQUARES &
           ((color == C_WHITE)
           ? (direction_shift(pawns & ~BB_FILE_E, D_NE)) | (direction_shift(pawns & ~BB_FILE_A, D_NW)) 
           : (direction_shift(pawns & ~BB_FILE_E, D_SE)) | (direction_shift(pawns & ~BB_FILE_A, D_SW)));
}

Bitboard attacks_knights(Bitboard knights) {
    return BB_ALL_SQUARES &
           ((direction_shift(knights & ~BB_FILE_E, D_NNE)) |
            (direction_shift(knights & ~BB_FILE_E, D_SSE)) |
            (direction_shift(knights & ~BB_FILE_A, D_SSW)) |
            (direction_shift(knights & ~BB_FILE_A, D_NNW)) |
            (direction_shift(knights & ~(BB_FILE_D | BB_FILE_E), D_NEE)) |
            (direction_shift(knights & ~(BB_FILE_D | BB_FILE_E), D_SEE)) |
            (direction_shift(knights & ~(BB_FILE_A | BB_FILE_B), D_SWW)) |
            (direction_shift(knights & ~(BB_FILE_A | BB_FILE_B), D_NWW)));
}

Bitboard attacks_bishops(Bitboard bishops, Bitboard occupied) {
    Bitboard res = 0;
    while (bishops)
        res |= attacks_bishop(pop_lsb32(&bishops), occupied);
    return res;
}

Bitboard attacks_rooks(Bitboard rooks, Bitboard occupied) {
    Bitboard res = 0;
    while (rooks)
        res |= attacks_rook(pop_lsb32(&rooks), occupied);
    return res;
}

Bitboard attacks_queens(Bitboard queens, Bitboard occupied) {
    return attacks_bishops(queens, occupied) | attacks_rooks(queens, occupied);
}

Bitboard attacks_kings(Bitboard kings) {
    return BB_ALL_SQUARES & 
           ((direction_shift(kings, D_N)) |
            (direction_shift(kings, D_S)) |
            (direction_shift(kings & ~BB_FILE_E, D_E)) |
            (direction_shift(kings & ~BB_FILE_A, D_W)) |
            (direction_shift(kings & ~BB_FILE_E, D_NE)) |
            (direction_shift(kings & ~BB_FILE_E, D_SE)) |
            (direction_shift(kings & ~BB_FILE_A, D_SW)) |
            (direction_shift(kings & ~BB_FILE_A, D_NW)));
}
