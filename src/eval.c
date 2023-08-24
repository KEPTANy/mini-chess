#include "mini_chess.h"

static const Score OP_PIECE_SCORE[PIECE_TYPE_NUM] = { 82, 337, 365, 477, 1025, 69420 },
                   EG_PIECE_SCORE[PIECE_TYPE_NUM] = { 94, 281, 297, 512,  936, 69420 };

static const Score OP_SCORE = 4182, EG_SCORE = 522;

static Score game_phase_score(Position *pos) {
    Score score = 0;
    for (PieceType t = PT_PAWN; t < PT_KING; t++)
        score += popcnt32(pos->piece[t]) * OP_PIECE_SCORE[t];
    return score;
}

Score evaluate(Position *pos) {
    Score op_score = 0, eg_score = 0;

    Score gp_score = game_phase_score(pos);
    GamePhase phase;
    if (gp_score > OP_SCORE)
        phase = GP_OPENING;
    else if (gp_score < EG_SCORE)
        phase = GP_ENDGAME;
    else
        phase = GP_MIDGAME;

    for (PieceType t = PT_PAWN; t < PIECE_TYPE_NUM; t++) {
        Bitboard bb = pos->piece[t];

        op_score += popcnt32(bb & pos->color[C_WHITE]) * OP_PIECE_SCORE[t];
        op_score -= popcnt32(bb & pos->color[C_BLACK]) * OP_PIECE_SCORE[t];

        eg_score += popcnt32(bb & pos->color[C_WHITE]) * EG_PIECE_SCORE[t];
        eg_score -= popcnt32(bb & pos->color[C_BLACK]) * EG_PIECE_SCORE[t];
    }

    if (phase == GP_OPENING)
        return op_score;
    else if (phase == GP_ENDGAME)
        return eg_score;
    else
        return (op_score * gp_score + eg_score * (OP_SCORE - gp_score)) / OP_SCORE;
}

Score evaluate_relative(Position *pos) {
    return (pos->side_to_move == C_WHITE) ? evaluate(pos) : -evaluate(pos);
}
