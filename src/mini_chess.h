#ifndef MINI_CHESS_H
#define MINI_CHESS_H

#include <time.h>
#include <inttypes.h>
#include <stdbool.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

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

// Move encoding:
//
// 00000000 00000000 00000000 00011111 - source square
// 00000000 00000000 00000011 11100000 - target square
// 00000000 00000000 00111100 00000000 - moving piece
// 00000000 00000011 11000000 00000000 - promoted piece
// 00000000 00111100 00000000 00000000 - captured piece
// 00000000 01000000 00000000 00000000 - promotion flag
// 00000000 10000000 00000000 00000000 - capture flag

typedef uint32_t Move;

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

typedef uint8_t GamePhase;
enum {
    GP_OPENING,
    GP_MIDGAME,
    GP_ENDGAME
};

typedef uint8_t GameState;
enum {
    GS_ONGOING,
    GS_DRAW,
    GS_WHITE_WIN,
    GS_BLACK_WIN
};

typedef int32_t Score;
enum {
    SCORE_INFINITY = 2000000000,
    SCORE_MATE = 1000000000,
    SCORE_DRAW = 0
};

typedef uint64_t Hash;

typedef struct Position {
    Hash     hash;
    Bitboard color[COLOR_NUM];
    Bitboard piece[PIECE_TYPE_NUM];
    uint16_t rule50;
    uint16_t ply;
    Color    side_to_move;
    bool     can_promote[PIECE_TYPE_NUM];
} Position;

// Table below shows upper bound on number of moves each piece can make
//
// Pawn   12 (4 promotions * 3 squares)
// Knight 8
// Bishop 8
// Rook   9
// Queen  17
// King   8
//
// Position where each side has 5 pawns, king, queen, 2 rooks and knight/bishop has number of moves <= 222 moves
// With all pawns promoted to queens number of moves is <= 272

#ifndef MOVELIST_MAX_SIZE
#define MOVELIST_MAX_SIZE 272
#endif

typedef struct MoveList {
    Move list[MOVELIST_MAX_SIZE];
    uint16_t size;
} MoveList;

#ifndef MAX_PLIES
#define MAX_PLIES 512
#endif

typedef struct GameHistory {
    Hash list[MAX_PLIES];
    uint16_t size;
} GameHistory;

extern GameHistory history;

#ifndef MAX_SEARCH_DEPTH
#define MAX_SEARCH_DEPTH 64
#endif

typedef struct PVLine {
    Move list[MOVELIST_MAX_SIZE];
    uint8_t size;
} PVLine;

extern PVLine pv_line;

extern bool nonstop;
extern clock_t stop_time;

// attacks.c

void attacks_init();
Bitboard attacks_pawn(Square square, Color color);
Bitboard attacks_knight(Square square);
Bitboard attacks_bishop(Square square, Bitboard occupied);
Bitboard attacks_rook(Square square, Bitboard occupied);
Bitboard attacks_queen(Square square, Bitboard occupied);
Bitboard attacks_king(Square square);
Bitboard attacks_pawns(Bitboard pawns, Color color);
Bitboard attacks_knights(Bitboard knights);
Bitboard attacks_bishops(Bitboard bishops, Bitboard occupied);
Bitboard attacks_rooks(Bitboard rooks, Bitboard occupied);
Bitboard attacks_queens(Bitboard queens, Bitboard occupied);
Bitboard attacks_kings(Bitboard kings);

// bitboard.c

Bitboard bitboard_of_square(Square square);
Bitboard bitboard_of_file(File file);
Bitboard bitboard_of_rank(Rank rank);

// bitops.c

int32_t popcnt32(uint32_t n);
int32_t popcnt64(uint64_t n);
int32_t lsb32(uint32_t n);
int32_t lsb64(uint64_t n);
int32_t msb32(uint32_t n);
int32_t msb64(uint64_t n);
int32_t pop_lsb32(uint32_t *n);
int32_t pop_lsb64(uint64_t *n);

// color.c

Color color_inverse(Color color);

// direction.c

Bitboard direction_shift(Bitboard bitboard, Direction direction);

// eval.c

Score evaluate(Position *pos);
Score evaluate_relative(Position *pos);

// history.c

void history_push(Hash hash);
void history_pop();
bool history_is_repetition_draw(Hash hash);

// misc.c

void mini_chess_init();
void print_move(Move move);
Move str_to_move(char *str);
void main_loop();

// move.c

Move   move_create(Square source, Square target, Piece moving, Piece promoted, Piece captured, bool is_promotion, bool is_capture);
Square move_get_source(Move move);
Square move_get_target(Move move);
Piece  move_get_moving_piece(Move move);
Piece  move_get_promoted_piece(Move move);
Piece  move_get_captured_piece(Move move);
bool   move_is_promotion(Move move);
bool   move_is_capture(Move move);
bool   move_is_legal(Position *pos, Move move);

// movegen.c

void movegen(Position *pos, MoveList *list, bool only_captures);

// movelist.c

void movelist_push(MoveList *list, Move move);
void movelist_pop(MoveList *list);
void movelist_sort(MoveList *list);

// piece.c

Piece     piece_create(Color color, PieceType type);
Color     piece_get_color(Piece piece);
PieceType piece_get_type(Piece piece);
Piece     char_to_piece(char c);
char      piece_to_char(Piece p);
char      piece_type_to_char(PieceType t);

// position.c

void      position_init();
void      position_set(Position *pos, char *fen);
Hash      position_get_hash(Position *pos);
GameState position_get_game_state(Position *pos);
bool      position_equal(Position *a, Position *b);
Bitboard  position_attacks(Position *pos, Color side);
void      position_apply(Position *pos, Move move);

// random.c

void     random_init(uint32_t seed);
uint32_t random32();
uint64_t random64();

// search.c

int   perft(Position *pos, int depth);
Score search(Position *pos, int ms);

// square.c

Square  square_create(File file, Rank rank);
File    square_get_file(Square square);
Rank    square_get_rank(Square square);
uint8_t square_distance(Square a, Square b);
Square  square_flip(Square s);

#endif
