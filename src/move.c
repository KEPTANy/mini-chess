#include "mini_chess.h"

Move move_create(Square source, Square destination, bool is_capture) {
    return (source) | (destination << 5) | (is_capture << 10);
}

Move move_promotion_create(Square source, Square destination, Piece promoted_to, bool is_capture) {
    return (move_create(source, destination, is_capture)) | (promoted_to << 11) | (1 << 15);
}

Square move_get_source(Move move) {
    return move & 0b11111;
}

Square move_get_destination(Move move) {
    return (move >> 5) & 0b11111;
}

Piece move_get_promotion_type(Move move) {
    return (move >> 11) & 0b1111;
}

bool move_is_capture(Move move) {
    return (move >> 10) & 1;
}

bool move_is_promotion(Move move) {
    return move >> 15;
}
