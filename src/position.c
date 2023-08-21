#include "mini_chess.h"

#include <string.h>
#include <stdio.h>

void position_set(Position *pos, char *fen) {
    memset(pos->color, 0, 2 * sizeof(Bitboard));
    memset(pos->piece, 0, 6 * sizeof(Bitboard));
    memset(pos->can_promote, 0, 6 * sizeof(bool));

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
    sscanf(fen, "%hu %hu", &pos->rule50, &pos->move_count);
}

bool position_equal(Position *a, Position *b) {
    if (a->side_to_move != a->side_to_move)
        return false;

    for (Color c = 0; c < COLOR_NUM; c++)
        if (a->color[c] != b->color[c])
            return false;

    for (PieceType pt = 0; pt < PIECE_TYPE_NUM; pt++)
        if (a->piece[pt] != b->piece[pt])
            return false;

    return true;
}

Bitboard position_attacks(Position *pos, Color side) {
    Bitboard all = pos->color[C_WHITE] & pos->color[C_BLACK];
    Bitboard clr = pos->color[side];

    return attacks_pawns(pos->piece[PT_PAWN] & clr, side) |
           attacks_knights(pos->piece[PT_KNIGHT] & clr) |
           attacks_bishops(pos->piece[PT_BISHOP] & clr, all) |
           attacks_rooks(pos->piece[PT_ROOK] & clr, all) |
           attacks_queens(pos->piece[PT_QUEEN] & clr, all) |
           attacks_kings(pos->piece[PT_KING] & clr);
}

void position_apply_move(Position *pos, Move move) {
    Square src = move_get_source(move);
    Square dst = move_get_target(move);
    Piece piece = move_get_moving_piece(move);
    PieceType type = piece_get_type(piece);
    Color stm = piece_get_color(piece);

    // clear source square
    pos->color[stm] &= ~bitboard_of_square(src);
    pos->piece[type] &= ~bitboard_of_square(src);

    // clear destination square
    if (move_is_capture(move)) {
        pos->rule50 = 0;
        pos->color[color_inverse(stm)] &= ~bitboard_of_square(dst);
        for (PieceType t = 0; t < PIECE_TYPE_NUM; t++)
            pos->piece[t] &= ~bitboard_of_square(dst);
    }

    if (type == PT_PAWN)
        pos->rule50 = 0;

    // place piece
    pos->color[stm] |= bitboard_of_square(dst);
    if (move_is_promotion(move))
        pos->piece[piece_get_type(move_get_promoted_piece(move))] |= bitboard_of_square(dst);
    else
        pos->piece[type] |= bitboard_of_square(dst);

    // set move counter
    if (stm == C_BLACK) {
        pos->move_count++;
        pos->rule50++;
    }

    // change side to move
    pos->side_to_move = color_inverse(stm);
}

void position_print(Position *pos) {
    for (Rank r = R_6; r < RANK_NUM; r--) {
        for (File f = F_A; f < FILE_NUM; f++) {
            Square sqr = square_create(f, r);
            Bitboard bb = bitboard_of_square(sqr);

            bool printed = false;
            for (Piece p = 0; p < PIECE_NUM; p++) {
                if ((pos->piece[piece_get_type(p)] & bb) && (pos->color[piece_get_color(p)] & bb)) {
                    printf("%c ", piece_to_char(p));
                    printed = true;
                    break;
                }
            }
            if (!printed)
                printf(". ");
        }
        printf("\n");
    }
    printf("Side to move: %s\nMove: %hu\n50-move-rule: %hu\n",
            (pos->side_to_move == C_WHITE) ? "white" : "black",
            pos->move_count,
            pos->rule50);
}

int perft(Position *pos, int depth) {
    MoveList list;
    list.size = 0;
    movegen_legal(pos, pos->side_to_move, &list, false);

    if (depth == 0)
        return 1;

    int res = 0;
    for (int i = 0; i < list.size; i++) {
        Position pos_cpy = *pos;
        position_apply_move(&pos_cpy, list.list[i]);
        res += perft(&pos_cpy, depth - 1);
    }
    return res;
}
