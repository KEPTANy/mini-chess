#include "mini_chess.h"

Move move_create(Square source, Square target, Piece moving, Piece promoted, Piece captured, bool is_promotion, bool is_capture) {
    return ((source       & 0b11111) << 0)  |
           ((target       & 0b11111) << 5)  |
           ((moving       & 0b1111)  << 10) |
           ((promoted     & 0b1111)  << 14) |
           ((captured     & 0b1111)  << 18) |
           ((is_promotion ? 1 : 0)   << 22) |
           ((is_capture   ? 1 : 0)   << 23);
}

Square move_get_source(Move move) {
    return (move >> 0) & 0b11111;
}

Square move_get_target(Move move) {
    return (move >> 5) & 0b11111;
}

Piece move_get_moving_piece(Move move) {
    return (move >> 10) & 0b1111;
}

Piece move_get_promoted_piece(Move move) {
    return (move >> 14) & 0b1111;
}

Piece move_get_captured_piece(Move move) {
    return (move >> 18) & 0b1111;
}

bool move_is_promotion(Move move) {
    return (move >> 22) & 0b1;
}

bool move_is_capture(Move move) {
    return (move >> 23) & 0b1;
}

bool move_is_legal(Position *pos, Move move) {
    Position cpy = *pos;
    position_apply(&cpy, move);
    return (position_attacks(&cpy, cpy.side_to_move) & cpy.piece[PT_KING] & cpy.color[pos->side_to_move]) == 0;
}
