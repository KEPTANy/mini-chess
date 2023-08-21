#include "mini_chess.h"

#include <string.h>

void movelist_push(MoveList *list, Move move) {
    list->list[list->size++] = move;
}

void movelist_pop(MoveList *list) {
    list->size--;
}

int movelist_find_move(MoveList *list, char *move) {
    Move curr;
    static char ranks[] = "123456";
    static char files[] = "abcde";
    for (int i = 0; i < list->size; i++) {
        curr = list->list[i];
        Square src = move_get_source(curr), trg = move_get_target(curr);
        if (files[square_get_file(src)] == move[0] &&
            ranks[square_get_rank(src)] == move[1] &&
            files[square_get_file(trg)] == move[2] &&
            ranks[square_get_rank(trg)] == move[3] &&
            ((move_is_promotion(curr) && (move[4] == piece_type_to_char(piece_get_type(move_get_promoted_piece(curr))))) ||
             (!move_is_promotion(curr) && (move[4] == '\0' || move[4] == '\n' || move[4] == ' '))))
            return i;
    }
    return -1;
}

static int cmp(const void *m1, const void *m2) {
    Move a = *((Move *)m1);
    Move b = *((Move *)m2);
    return (move_is_promotion(b) * 2 + move_is_capture(b)) - (move_is_promotion(a) * 2 + move_is_capture(a));
}

void movelist_sort(MoveList *list) {
    qsort(list->list, (size_t)list->size, sizeof(Move), cmp);
}
