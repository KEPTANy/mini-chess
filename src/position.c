#include "mini_chess.h"

bool position_equal(Position *a, Position *b) {
    if (a->side_to_move != a->side_to_move)
        return false;

    for (Color c = 0; c < COLOR_NUM; c++)
        if (a->color[c] != b->color[c])
            return false;

    for (PieceType pt = 0; pt < PIECE_TYPE_NUM; pt++)
        if (a->piece[pt] != b->piece[pt])
            return false;

    return true;
}

Bitboard position_attacks(Position *pos, Color side) {
    Bitboard all = pos->color[C_WHITE] & pos->color[C_BLACK];
    Bitboard clr = pos->color[side];

    return attacks_pawns(pos->piece[PT_PAWN] & clr, side) |
           attacks_knights(pos->piece[PT_KNIGHT] & clr) |
           attacks_bishops(pos->piece[PT_BISHOP] & clr, all) |
           attacks_rooks(pos->piece[PT_ROOK] & clr, all) |
           attacks_queens(pos->piece[PT_QUEEN] & clr, all) |
           attacks_kings(pos->piece[PT_KING] & clr);
}
