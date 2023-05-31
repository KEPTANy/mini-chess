#ifndef MINI_CHESS_H
#define MINI_CHESS_H

#include <inttypes.h>

typedef uint8_t Color;
enum {
    C_WHITE,
    C_BLACK,

    COLOR_NUM
};

typedef uint8_t PieceType;
enum {
    PT_PAWN,
    PT_KNIGHT,
    PT_BISHOP,
    PT_ROOK,
    PT_QUEEN,
    PT_KING,

    PIECE_TYPE_NUM
};

typedef uint8_t Piece;
enum {
    P_WHITE_PAWN,   P_BLACK_PAWN,
    P_WHITE_KNIGHT, P_BLACK_KNIGHT,
    P_WHITE_BISHOP, P_BLACK_BISHOP,
    P_WHITE_ROOK,   P_BLACK_ROOK,
    P_WHITE_QUEEN,  P_BLACK_QUEEN,
    P_WHITE_KING,   P_BLACK_KING,

    PIECE_NUM
};

// color.c
Color color_inverse(Color color);

// piece.c
Piece     piece_create(Color color, PieceType type);
Color     piece_get_color(Piece piece);
PieceType piece_get_type(Piece piece);

#endif
