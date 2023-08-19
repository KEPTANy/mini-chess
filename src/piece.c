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

Piece char_to_piece(char c) {
    static Piece arr[] = {
        ['P'] = P_WHITE_PAWN,   ['p'] = P_BLACK_PAWN,
        ['N'] = P_WHITE_KNIGHT, ['n'] = P_BLACK_KNIGHT,
        ['B'] = P_WHITE_BISHOP, ['b'] = P_BLACK_BISHOP,
        ['R'] = P_WHITE_ROOK,   ['r'] = P_BLACK_ROOK,
        ['Q'] = P_WHITE_QUEEN,  ['q'] = P_BLACK_QUEEN,
        ['K'] = P_WHITE_KING,   ['k'] = P_BLACK_KING
    };
    return arr[c];
}

char piece_to_char(Piece p) {
    return "PpNnBbRrQqKk"[p];
}

char piece_type_to_char(PieceType t) {
    return "pnbrqk"[t];
}
