#include "mini_chess.h"

static Score PT_TO_SCORE[PIECE_TYPE_NUM] = {
    100, 342, 374, 530, 911, 72727
};

Score evaluate(Position *pos) {
    MoveList list;
    list.size = 0;
    movegen_legal(pos, pos->side_to_move, &list, false);

    if (list.size == 0) {
        Bitboard atk = position_attacks(pos, color_inverse(pos->side_to_move));
        if (atk & pos->piece[PT_KING] & pos->color[pos->side_to_move])
            return (pos->side_to_move == C_WHITE) ? -INT32_MAX : INT32_MAX;
        return 0;
    }

    Score material = 0;
    for (PieceType t = PT_PAWN; t < PIECE_TYPE_NUM; t++) {
        Bitboard bb = pos->piece[t];
        material += popcnt32(bb & pos->color[C_WHITE]) * PT_TO_SCORE[t];
        material -= popcnt32(bb & pos->color[C_BLACK]) * PT_TO_SCORE[t];
    }

    return material;
}
