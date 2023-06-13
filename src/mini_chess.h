#ifndef MINI_CHESS_H
#define MINI_CHESS_H

#include <inttypes.h>
#include <stdbool.h>

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

typedef int8_t Direction;
enum {
    D_N = FILE_NUM,
    D_E = 1,
    D_S = -D_N,
    D_W = -D_E,

    D_NE = D_N + D_E,
    D_SE = D_S + D_E,
    D_SW = D_S + D_W,
    D_NW = D_N + D_W,

    D_NNE = D_N + D_N + D_E,
    D_NEE = D_N + D_E + D_E,
    D_SEE = D_S + D_E + D_E,
    D_SSE = D_S + D_S + D_E,
    D_SSW = D_S + D_S + D_W,
    D_SWW = D_S + D_W + D_W,
    D_NWW = D_N + D_W + D_W,
    D_NNW = D_N + D_N + D_W,
};

typedef uint32_t Bitboard;
enum {
    BB_FILE_A = 0b000010000100001000010000100001,
    BB_FILE_B = 0b000100001000010000100001000010,
    BB_FILE_C = 0b001000010000100001000010000100,
    BB_FILE_D = 0b010000100001000010000100001000,
    BB_FILE_E = 0b100001000010000100001000010000,

    BB_RANK_1 = 0b000000000000000000000000011111,
    BB_RANK_2 = 0b000000000000000000001111100000,
    BB_RANK_3 = 0b000000000000000111110000000000,
    BB_RANK_4 = 0b000000000011111000000000000000,
    BB_RANK_5 = 0b000001111100000000000000000000,
    BB_RANK_6 = 0b111110000000000000000000000000,

    BB_DARK_SQUARES  = 0b010101010101010101010101010101,
    BB_LIGHT_SQUARES = 0b101010101010101010101010101010,
    BB_ALL_SQUARES   = 0b111111111111111111111111111111
};

typedef struct Position {
    Bitboard color[COLOR_NUM];
    Bitboard piece[PIECE_TYPE_NUM];
    Color    side_to_move;
    uint8_t  rule50;
    uint16_t move_count;
} Position;

// bitboard.c

Bitboard bitboard_of_square(Square square);
Bitboard bitboard_of_file(File file);
Bitboard bitboard_of_rank(Rank rank);

// color.c

Color color_inverse(Color color);

// direction.c

Bitboard direction_shift(Bitboard bitboard, Direction direction);

// piece.c

Piece     piece_create(Color color, PieceType type);
Color     piece_get_color(Piece piece);
PieceType piece_get_type(Piece piece);

// position.c

bool position_are_equal(Position *a, Position *b);

// square.c

Square square_create(File file, Rank rank);
File   square_get_file(Square square);
Rank   square_get_rank(Square square);

#endif
