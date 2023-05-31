#include "mini_chess.h"

Piece piece_create(Color color, PieceType type) {
    return color | (type << 1);
}

Color piece_get_color(Piece piece) {
    return piece & 1;
}

PieceType piece_get_type(Piece piece) {
    return piece >> 1;
}
