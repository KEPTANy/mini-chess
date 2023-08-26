#include "mini_chess.h"

#include <stdlib.h>

clock_t stop_time;
bool nonstop;

static Score quiescence(Position *pos, Score alpha, Score beta) {
    GameState state = position_get_game_state(pos);

    if (state == GS_DRAW)
        return SCORE_DRAW;
    else if (state != GS_ONGOING)
        return -SCORE_MATE;

    Score eval = evaluate_relative(pos);

    if (eval >= beta)
        return beta;

    if (eval > alpha)
        alpha = eval;

    MoveList list;
    movegen(pos, &list, true);
    movelist_sort(&list);

    Position cpy = *pos;
    for (int i = 0; i < list.size; i++) {
        if (!nonstop && clock() > stop_time)
            return 0;

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
    GameState state = position_get_game_state(pos);

    if (state == GS_DRAW)
        return SCORE_DRAW;
    else if (state != GS_ONGOING)
        return -SCORE_MATE - depth;

    if (depth == 0)
        return quiescence(pos, alpha, beta);

    MoveList list;
    movegen(pos, &list, false);
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

Score search(Position *pos, int ms) {
    Score best, curr;
    pv_line.size = 0;
    nonstop = true;
    stop_time = clock() + ms * CLOCKS_PER_SEC / 1000;

    PVLine buffer;
    for (int depth = 1; depth <= MAX_SEARCH_DEPTH && abs(best) <= SCORE_MATE; depth++) {
        for (int i = pv_line.size; i > 0; i--)
            pv_line.list[i] = pv_line.list[i - 1];
        pv_line.size++;

        curr = negamax(pos, -SCORE_INFINITY, SCORE_INFINITY, depth);

        nonstop = false;
        if (clock() > stop_time && depth > 1) {
            pv_line = buffer;
            break;
        } else {
            buffer = pv_line;
            if (curr > SCORE_MATE)
                best = SCORE_MATE + depth - (curr - SCORE_MATE);
            else if (curr < -SCORE_MATE)
                best = -(SCORE_MATE + depth - (-curr + SCORE_MATE));
            else
                best = curr;
        }
    }
    return (pos->side_to_move == C_BLACK) ? -best : best;
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
