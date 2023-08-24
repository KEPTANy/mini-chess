#include "mini_chess.h"

void movegen(Position *pos, MoveList *list, bool only_captures) {
    list->size = 0;

    Color stm = pos->side_to_move;
    Color inv = color_inverse(stm);
    Bitboard stm_bb = pos->color[stm];
    Bitboard inv_bb = pos->color[inv];
    Bitboard all_bb = stm_bb | inv_bb;

    for (PieceType pt = 0; pt < PIECE_TYPE_NUM; pt++) {
        Bitboard bb = pos->piece[pt] & stm_bb;

        while (bb) {
            Square src = pop_lsb32(&bb);
            Bitboard trg_bb = ~stm_bb;

            switch (pt) {
            case PT_PAWN:
                trg_bb = (~all_bb & direction_shift(bitboard_of_square(src), (stm == C_WHITE) ? D_N : D_S)) |
                         (attacks_pawn(src, stm) & inv_bb);
                break;
            case PT_KNIGHT: trg_bb &= attacks_knight(src);         break;
            case PT_BISHOP: trg_bb &= attacks_bishop(src, all_bb); break;
            case PT_ROOK:   trg_bb &= attacks_rook(src, all_bb);   break;
            case PT_QUEEN:  trg_bb &= attacks_queen(src, all_bb);  break;
            case PT_KING:   trg_bb &= attacks_king(src);           break;
            }

            if (only_captures)
                trg_bb &= inv_bb;

            while (trg_bb) {
                Square trg = pop_lsb32(&trg_bb);
                Piece captured;
                Move move;

                if (bitboard_of_square(trg) & inv_bb) {
                    for (PieceType cap = 0; cap < PIECE_TYPE_NUM; cap++) {
                        if (bitboard_of_square(trg) & pos->piece[cap]) {
                            captured = piece_create(inv, cap);
                            break;
                        }
                    }
                }

                if (pt == PT_PAWN && (square_get_rank(trg) == R_1 || square_get_rank(trg) == R_6)) {
                    for (PieceType prom = PT_KNIGHT; prom <= PT_QUEEN; prom++) {
                        if (!pos->can_promote[prom])
                            continue;

                        move = move_create(src, trg, piece_create(stm, pt), piece_create(stm, prom), captured, 1, bitboard_of_square(trg) & inv_bb);

                        if (move_is_legal(pos, move))
                            movelist_push(list, move);
                    }
                } else {
                    move = move_create(src, trg, piece_create(stm, pt), 0, captured, 0, inv_bb & bitboard_of_square(trg));

                    if (move_is_legal(pos, move))
                        movelist_push(list, move);
                }
            }
        }
    }
}
