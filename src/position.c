#include "mini_chess.h"

bool position_are_equal(Position *a, Position *b) {
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
