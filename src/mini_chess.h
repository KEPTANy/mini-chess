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

typedef uint8_t File;
enum {
    F_A, F_B, F_C, F_D, F_E,

    FILE_NUM
};

typedef uint8_t Rank;
enum {
    R_1, R_2, R_3, R_4, R_5, R_6,

    RANK_NUM
};

typedef uint8_t Square;
enum {
    S_A1, S_B1, S_C1, S_D1, S_E1,
    S_A2, S_B2, S_C2, S_D2, S_E2,
    S_A3, S_B3, S_C3, S_D3, S_E3,
    S_A4, S_B4, S_C4, S_D4, S_E4,
    S_A5, S_B5, S_C5, S_D5, S_E5,
    S_A6, S_B6, S_C6, S_D6, S_E6,

    SQUARE_NUM
};

// color.c
Color color_inverse(Color color);

// piece.c
Piece     piece_create(Color color, PieceType type);
Color     piece_get_color(Piece piece);
PieceType piece_get_type(Piece piece);

// square.c
Square square_create(File file, Rank rank);
File   square_get_file(Square square);
Rank   square_get_rank(Square square);

#endif
