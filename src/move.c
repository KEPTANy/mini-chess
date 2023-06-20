#include "mini_chess.h"

Move move_create(Square source, Square destination) {
    return (source & 0b11111) | ((destination & 0b11111) << 5);
}

Move move_promotion_create(Square source, Square destination, Piece promoted_to) {
    return (move_create(source, destination)) | ((promoted_to & 0b1111) << 11) | (1 << 10);
}

Square move_get_source(Move move) {
    return move & 0b11111;
}

Square move_get_destination(Move move) {
    return (move >> 5) & 0b11111;
}

Piece move_get_promotion(Move move) {
    return (move >> 11) & 0b1111;
}

bool move_is_promotion(Move move) {
    return (move >> 10) & 0b1;
}
