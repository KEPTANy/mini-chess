#include <stdio.h>
#include <string.h>
#include <time.h>

#include "mini_chess.h"

void mini_chess_init() {
    attacks_init();
    square_init();
}

int main(int argc, char **argv) {
    mini_chess_init();

    Position pos;
    MoveList list;

    setbuf(stdin, NULL);
    setbuf(stdout, NULL);

    char input[2048];

    while (1) {
        fflush(stdout);

        memset(input, 0, sizeof(input) * sizeof(char));

        if (!fgets(input, 2048, stdin))
            continue;

        if (input[0] == '\n')
            continue;

        if (strncmp(input, "quit", 4) == 0) {
            break;
        } else if (strncmp(input, "position", 8) == 0) {
            position_set(&pos, input + 9);
        } else if (strncmp(input, "print", 5) == 0) {
            position_print(&pos);
        } else if (strncmp(input, "movelist", 8) == 0) {
            list.size = 0;
            movegen_legal(&pos, pos.side_to_move, &list);
            printf("Movelist for current position (%d moves):\n", list.size);
            for (int i = 0; i < list.size; i++) {
                move_print(list.list[i]);
                printf("\n");
            }
        } else if (strncmp(input, "islegal", 7) == 0) {
            list.size = 0;
            movegen_legal(&pos, pos.side_to_move, &list);
            if (movelist_find_move(&list, input + 8) != -1)
                puts("Legal");
            else
                puts("Illegal");
        } else if (strncmp(input, "apply", 5) == 0) {
            list.size = 0;
            movegen_legal(&pos, pos.side_to_move, &list);
            int index = movelist_find_move(&list, input + 6);
            if (index != -1) 
                position_apply_move(&pos, list.list[index]);
            else
                puts("Illegal move");
        } else if (strncmp(input, "perft", 5) == 0) {
            int depth = atoi(input + 6);
            clock_t timer = clock();
            int res = perft(&pos, depth);
            timer = clock() - timer;
            double seconds = ((double)timer) / CLOCKS_PER_SEC;
            printf("Perft for depth %d: %d moves (%lf seconds, %lf NPS)\n", depth, res, seconds, res / seconds);
        }
    }

    return 0;
}
