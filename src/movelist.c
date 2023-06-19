#include "mini_chess.h"

void movelist_push(MoveList *list, Move move) {
    list->list[list->size++] = move;
}

void movelist_pop(MoveList *list) {
    list->size--;
}
