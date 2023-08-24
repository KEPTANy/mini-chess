#include "mini_chess.h"

GameHistory history;

void history_push(Hash hash) {
    history.list[history.size++] = hash;
}

void history_pop() {
    history.size--;
}

bool history_is_repetition_draw(Hash hash) {
    int cnt = 0;
    for (int i = 0; i < history.size; i++)
        if (hash == history.list[i])
            cnt++;
    return cnt > 2;
}
