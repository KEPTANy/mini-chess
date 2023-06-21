#include "mini_chess.h"

Move move_create(Square source, Square target, Piece moving, Piece promoted, bool is_promotion, bool is_capture) {
    return ((source       & 0b11111) << 0)  |
           ((target       & 0b11111) << 5)  |
           ((moving       & 0b1111)  << 10) |
           ((promoted     & 0b1111)  << 14) |
           ((is_promotion ? 1 : 0)   << 18) |
           ((is_capture   ? 1 : 0)   << 19);
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

bool move_is_promotion(Move move) {
    return (move >> 18) & 0b1;
}

bool move_is_capture(Move move) {
    return (move >> 19) & 0b1;
}
