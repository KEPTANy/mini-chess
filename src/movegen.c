#include "mini_chess.h"

#include <stdio.h>

void movegen_legal(Position *pos, Color stm, MoveList *list) {
    Color inv = color_inverse(stm);
    Bitboard all = pos->color[C_WHITE] | pos->color[C_BLACK];
    for (PieceType pt = 0; pt < PIECE_TYPE_NUM; pt++) {
        Bitboard bb = pos->piece[pt] & pos->color[stm];
        while (bb) {
            Square source = pop_lsb32(&bb);
            Bitboard targets;
            if (pt == PT_PAWN) {
                targets = ~all & direction_shift(bitboard_of_square(source), (stm == C_WHITE) ? D_N : D_S);
                targets |= attacks_pawn(source, stm) & pos->color[inv];

                while (targets) {
                    Square target = pop_lsb32(&targets);
                    if (targets && BB_RANK_1 || targets && BB_RANK_6) {
                        for (PieceType prom = PT_KNIGHT; prom <= PT_QUEEN; prom++) {
                            if (!pos->can_promote[prom])
                                continue;
                            Move move = move_create(source,
                                                    target,
                                                    piece_create(stm, pt),
                                                    piece_create(stm, prom),
                                                    1,
                                                    pos->color[inv] & bitboard_of_square(target));

                            if (move_is_legal(pos, move))
                                movelist_push(list, move);
                        }
                    } else {
                        Move move = move_create(source,
                                                target,
                                                piece_create(stm, pt),
                                                0,
                                                0,
                                                pos->color[inv] & bitboard_of_square(target));

                        if (move_is_legal(pos, move))
                            movelist_push(list, move);
                    }
                }
            } else {
                switch (pt) {
                case PT_KNIGHT:
                    targets = attacks_knight(source);      break;
                case PT_BISHOP:
                    targets = attacks_bishop(source, all); break;
                case PT_ROOK:
                    targets = attacks_rook(source, all);   break;
                case PT_QUEEN:
                    targets = attacks_queen(source, all);  break;
                case PT_KING:
                    targets = attacks_king(source);        break;
                }

                targets &= ~pos->color[stm];
                while (targets) {
                    Square target = pop_lsb32(&targets);
                    Move move = move_create(source,
                                            target,
                                            piece_create(stm, pt),
                                            0,
                                            0,
                                            pos->color[inv] & bitboard_of_square(target));

                    if (move_is_legal(pos, move))
                        movelist_push(list, move);
                }
            }
        }
    }
}
