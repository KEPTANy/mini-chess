#include "mini_chess.h"

Bitboard attacks_pawn(Square square, Color color) {
    return attacks_pawns(bitboard_of_square(square), color);
}

Bitboard attacks_knight(Square square) {
    return attacks_knights(bitboard_of_square(square));
}

Bitboard attacks_bishop(Square square, Bitboard occupied) {
    Bitboard res = 0;
    static const Direction dirs[] = { D_NE, D_SE, D_SW, D_NW };
    for (size_t i = 0; i < ARRAY_SIZE(dirs); i++) {
        for (Square curr = square + dirs[i];
             curr < SQUARE_NUM && square_distance(curr, curr - dirs[i]) == 1;
             curr += dirs[i]) {

            res |= bitboard_of_square(curr);
            if (occupied & bitboard_of_square(curr))
                break;
        }
    }
    return res;
}

Bitboard attacks_rook(Square square, Bitboard occupied) {
    Bitboard res = 0;
    static const Direction dirs[] = { D_N, D_S, D_E, D_W };
    for (size_t i = 0; i < ARRAY_SIZE(dirs); i++) {
        for (Square curr = square + dirs[i];
             curr < SQUARE_NUM && square_distance(curr, curr - dirs[i]) == 1;
             curr += dirs[i]) {

            res |= bitboard_of_square(curr);
            if (occupied & bitboard_of_square(curr))
                break;
        }
    }
    return res;
}

Bitboard attacks_queen(Square square, Bitboard occupied) {
    return attacks_bishop(square, occupied) | attacks_rook(square, occupied);
}

Bitboard attacks_king(Square square) {
    return attacks_kings(bitboard_of_square(square));
}

Bitboard attacks_pawns(Bitboard pawns, Color color) {
    if (color == C_WHITE)
        return (direction_shift(pawns & ~BB_FILE_E, D_NE)) |
               (direction_shift(pawns & ~BB_FILE_A, D_NW));
    else
        return (direction_shift(pawns & ~BB_FILE_E, D_SE)) |
               (direction_shift(pawns & ~BB_FILE_A, D_SW));
}

Bitboard attacks_knights(Bitboard knights) {
    return (direction_shift(knights & ~BB_FILE_E, D_NNE)) |
           (direction_shift(knights & ~BB_FILE_E, D_SSE)) |
           (direction_shift(knights & ~BB_FILE_A, D_SSW)) |
           (direction_shift(knights & ~BB_FILE_A, D_NNW)) |
           (direction_shift(knights & ~(BB_FILE_D | BB_FILE_E), D_NEE)) |
           (direction_shift(knights & ~(BB_FILE_D | BB_FILE_E), D_SEE)) |
           (direction_shift(knights & ~(BB_FILE_A | BB_FILE_B), D_SWW)) |
           (direction_shift(knights & ~(BB_FILE_A | BB_FILE_B), D_NWW));
}

Bitboard attacks_bishops(Bitboard bishops, Bitboard occupied) {
    Bitboard res = 0;
    for (Square s = S_A1; s < SQUARE_NUM; s++)
        if (bishops & bitboard_of_square(s))
            res |= attacks_bishop(s, occupied);
    return res;
}

Bitboard attacks_rooks(Bitboard rooks, Bitboard occupied) {
    Bitboard res = 0;
    for (Square s = S_A1; s < SQUARE_NUM; s++)
        if (rooks & bitboard_of_square(s))
            res |= attacks_rook(s, occupied);
    return res;
}

Bitboard attacks_queens(Bitboard queens, Bitboard occupied) {
    return attacks_bishops(queens, occupied) | attacks_rooks(queens, occupied);
}

Bitboard attacks_kings(Bitboard kings) {
    return (direction_shift(kings, D_N)) |
           (direction_shift(kings, D_S)) |
           (direction_shift(kings & ~BB_FILE_E, D_E)) |
           (direction_shift(kings & ~BB_FILE_A, D_W)) |
           (direction_shift(kings & ~BB_FILE_E, D_NE)) |
           (direction_shift(kings & ~BB_FILE_E, D_SE)) |
           (direction_shift(kings & ~BB_FILE_A, D_SW)) |
           (direction_shift(kings & ~BB_FILE_A, D_NW));
}
