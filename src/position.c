#include "mini_chess.h"

#include <stdio.h>
#include <string.h>

static Hash PIECE_HASH[SQUARE_NUM][PIECE_NUM];
static Hash COLOR_HASH;

void position_init() {
    for (Square s = S_A1; s < SQUARE_NUM; s++)
        for (Piece p = P_WHITE_PAWN; p < PIECE_NUM; p++)
            PIECE_HASH[s][p] = random64();

    COLOR_HASH = random64();
}

void position_set(Position *pos, char *fen) {
    memset(pos->color, 0, COLOR_NUM * sizeof(Bitboard));
    memset(pos->piece, 0, PIECE_TYPE_NUM * sizeof(Bitboard));
    memset(pos->can_promote, 0, PIECE_TYPE_NUM * sizeof(bool));
    history.size = 0;

    for (Rank r = R_6; r < RANK_NUM; r--) {
        for (File f = F_A; f < FILE_NUM; f++) {
            Square sqr = square_create(f, r);

            if (*fen == '/')
                fen++;

            if (*fen >= '0' && *fen <= '5') {
                f += *fen - '0' - 1;
            } else {
                Piece p = char_to_piece(*fen);
                pos->color[piece_get_color(p)] |= bitboard_of_square(sqr);
                pos->piece[piece_get_type(p)]  |= bitboard_of_square(sqr);
            }
            fen++;
        }
    }

    pos->side_to_move = (*(++fen) == 'w') ? C_WHITE : C_BLACK;
    fen += 2;

    while (*fen != ' ') {
        PieceType t = piece_get_type(char_to_piece(*fen));
        pos->can_promote[t] = true;
        fen++;
    }
    sscanf(fen, "%hu", &pos->rule50);
    pos->ply = 0;

    pos->hash = position_get_hash(pos);

    history_push(pos->hash);
}

Hash position_get_hash(Position *pos) {
    Hash hash = 0;

    for (Color c = C_WHITE; c < COLOR_NUM; c++) {
        for (PieceType t = PT_PAWN; t < PIECE_TYPE_NUM; t++) {
            Bitboard bb = pos->color[c] & pos->piece[t];

            while (bb) {
                Square s = pop_lsb32(&bb);
                hash ^= PIECE_HASH[s][piece_create(c, t)];
            }
        }
    }

    if (pos->side_to_move == C_BLACK)
        hash ^= COLOR_HASH;

    return hash;
}

bool position_equal(Position *a, Position *b) {
    return a->hash == b->hash;
}

Bitboard position_attacks(Position *pos, Color side) {
    Bitboard all = pos->color[C_WHITE] | pos->color[C_BLACK];
    Bitboard clr = pos->color[side];

    return attacks_pawns(pos->piece[PT_PAWN] & clr, side) |
           attacks_knights(pos->piece[PT_KNIGHT] & clr) |
           attacks_bishops(pos->piece[PT_BISHOP] & clr, all) |
           attacks_rooks(pos->piece[PT_ROOK] & clr, all) |
           attacks_queens(pos->piece[PT_QUEEN] & clr, all) |
           attacks_kings(pos->piece[PT_KING] & clr);
}

void position_apply(Position *pos, Move move) {
    Square src = move_get_source(move);
    Square trg = move_get_target(move);
    Piece piece = move_get_moving_piece(move);
    Piece promoted = move_get_promoted_piece(move);
    Piece captured = move_get_promoted_piece(move);
    PieceType type = piece_get_type(piece);
    Color stm = piece_get_color(piece);

    pos->color[stm] &= ~bitboard_of_square(src);
    pos->piece[type] &= ~bitboard_of_square(src);
    pos->hash ^= PIECE_HASH[src][piece];

    if (move_is_capture(move)) {
        pos->rule50 = 0;
        pos->color[color_inverse(stm)] &= ~bitboard_of_square(trg);
        pos->piece[piece_get_type(captured)] &= ~bitboard_of_square(trg);
        pos->hash ^= PIECE_HASH[trg][captured];
    }

    if (type == PT_PAWN)
        pos->rule50 = 0;

    pos->color[stm] |= bitboard_of_square(trg);
    if (move_is_promotion(move)) {
        pos->piece[piece_get_type(promoted)] |= bitboard_of_square(trg);
        pos->hash ^= PIECE_HASH[trg][promoted];
    } else {
        pos->piece[type] |= bitboard_of_square(trg);
        pos->hash ^= PIECE_HASH[trg][piece];
    }

    pos->rule50++;
    pos->ply++;

    pos->side_to_move = color_inverse(stm);
    pos->hash ^= COLOR_HASH;
}
