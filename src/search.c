#include "mini_chess.h"

clock_t stop_time;
bool nonstop;

static Score quiescence(Position *pos, Score alpha, Score beta) {
    if (!nonstop && clock() > stop_time)
        return 0;
    MoveList list;
    movegen(pos, &list, false);

    if (list.size == 0) {
        if (position_attacks(pos, color_inverse(pos->side_to_move)) & pos->piece[PT_KING] & pos->color[pos->side_to_move])
            return -SCORE_MATE;
        else
            return SCORE_DRAW;
    }

    if (pos->rule50 == 100 || history_is_repetition_draw(pos->hash))
        return SCORE_DRAW;

    Score eval = evaluate(pos);

    if (eval >= beta)
        return beta;

    if (eval > alpha)
        alpha = eval;

    movelist_sort(&list);

    Position cpy = *pos;
    for (int i = 0; i < list.size; i++) {
        if (!nonstop && clock() > stop_time)
            return 0;

        if (!move_is_capture(list.list[i]))
            continue;

        position_apply(pos, list.list[i]);
        history_push(pos->hash);
        Score score = -quiescence(pos, -beta, -alpha);
        history_pop();
        *pos = cpy;

        if (score >= beta)
            return beta;

        if (score > alpha)
            alpha = score;
    }
    return alpha;
}

static Score negamax(Position *pos, Score alpha, Score beta, int depth) {
    MoveList list;
    movegen(pos, &list, false);

    if (list.size == 0) {
        if (position_attacks(pos, color_inverse(pos->side_to_move)) & pos->piece[PT_KING] & pos->color[pos->side_to_move])
            return -SCORE_MATE - depth;
        else
            return SCORE_DRAW;
    }

    if (pos->rule50 == 100 || history_is_repetition_draw(pos->hash))
        return SCORE_DRAW;

    if (depth == 0)
        return quiescence(pos, alpha, beta);

    movelist_sort(&list);

    Position cpy = *pos;
    for (int i = 0; i < list.size; i++) {
        if (!nonstop && clock() > stop_time)
            return 0;

        position_apply(pos, list.list[i]);
        history_push(pos->hash);
        Score score = -negamax(pos, -beta, -alpha, depth - 1);
        history_pop();
        *pos = cpy;

        if (score >= beta)
            return beta;

        if (score > alpha) {
            alpha = score;
            pv_line.list[depth - 1] = list.list[i];
        }
    }
    return alpha;
}

void search(Position *pos, int ms) {
    pv_line.size = 1;
    nonstop = true;
    stop_time = clock() + ms * CLOCKS_PER_SEC / 1000;

    negamax(pos, -SCORE_INFINITY, SCORE_INFINITY, 1);

    nonstop = false;
    PVLine buffer = pv_line;
    for (int depth = 2; depth <= MAX_SEARCH_DEPTH; depth++) {
        for (int i = pv_line.size; i > 0; i--)
            pv_line.list[i] = pv_line.list[i - 1];
        pv_line.size++;

        negamax(pos, -SCORE_INFINITY, SCORE_INFINITY, 1);
        if (clock() > stop_time) {
            pv_line = buffer;
            break;
        } else {
            buffer = pv_line;
        }
    }
}

int perft(Position *pos, int depth) {
    if (depth == 0)
        return 1;

    MoveList list;
    movegen(pos, &list, false);

    int res = 0;
    Position cpy = *pos;
    for (int i = 0; i < list.size; i++) {
        position_apply(pos, list.list[i]);
        res += perft(pos, depth - 1);
        *pos = cpy;
    }
    return res;
}
