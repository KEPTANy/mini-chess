#include "mini_chess.h"

Score alpha_beta_max(Position *pos, Score alpha, Score beta, int depth) {
    if (clock() > stop_time)
        return 0;

    if (depth == 0)
        return evaluate(pos);
    MoveList list;
    list.size = 0;
    movegen_legal(pos, pos->side_to_move, &list, false);
    Position pos_cpy = *pos;
    for (int i = 0; i < list.size; i++) {
        position_apply_move(&pos_cpy, list.list[i]);
        Score score = alpha_beta_min(&pos_cpy, alpha, beta, depth - 1);
        if (score >= beta)
            return beta;
        if (score > alpha)
            alpha = score;
    }
    return alpha;
}

Score alpha_beta_min(Position *pos, Score alpha, Score beta, int depth) {
    if (clock() > stop_time)
        return 0;

    if (depth == 0)
        return -evaluate(pos);
    MoveList list;
    list.size = 0;
    movegen_legal(pos, pos->side_to_move, &list, false);
    Position pos_cpy = *pos;
    for (int i = 0; i < list.size; i++) {
        Score score = alpha_beta_max(&pos_cpy, alpha, beta, depth - 1);
        if (score <= alpha)
            return alpha;
        if (score < beta)
            beta = score;
    }
    return beta;
}
