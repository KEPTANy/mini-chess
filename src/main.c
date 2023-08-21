#include <stdio.h>
#include <string.h>
#include <time.h>

#include "mini_chess.h"

void mini_chess_init() {
    attacks_init();
    square_init();
}

clock_t stop_time;

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
            movegen_legal(&pos, pos.side_to_move, &list, false);

            printf("Movelist for current position (%d moves):\n", list.size);
            for (int i = 0; i < list.size; i++)
                move_print(list.list[i]);
        } else if (strncmp(input, "islegal", 7) == 0) {
            list.size = 0;
            movegen_legal(&pos, pos.side_to_move, &list, false);

            if (movelist_find_move(&list, input + 8) != -1)
                puts("Legal");
            else
                puts("Illegal");
        } else if (strncmp(input, "apply", 5) == 0) {
            list.size = 0;
            movegen_legal(&pos, pos.side_to_move, &list, false);

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
        } else if (strncmp(input, "stateval", 8) == 0) {
            Score eval = evaluate(&pos);
            printf("Eval: %d\n", eval);
        } else if (strncmp(input, "search", 6) == 0) {
            int ms = atoi(input + 7);
            stop_time = clock() + (ms * CLOCKS_PER_SEC / 1000);

            list.size = 0;
            movegen_legal(&pos, pos.side_to_move, &list, false);
            
            Move best, curr;
            for (int depth = 1; ; depth += 2) {
                Score best_score = (pos.side_to_move == C_WHITE) ? -INT32_MAX : INT32_MAX;
                for (int i = 0; i < list.size; i++) {
                    Position pos_cpy = pos;
                    position_apply_move(&pos_cpy, list.list[i]);
                    Score curr_score = (pos.side_to_move == C_WHITE) ? alpha_beta_min(&pos_cpy, INT32_MAX, -INT32_MAX, depth)
                                                                     : alpha_beta_max(&pos_cpy, INT32_MAX, -INT32_MAX, depth);

                    if ((pos.side_to_move == C_WHITE && curr_score >= best_score) ||
                        (pos.side_to_move == C_BLACK && curr_score <= best_score)) {
                        curr = list.list[i];
                    }

                    if (clock() > stop_time)
                        break;
                }


                if (clock() > stop_time)
                    break;
                else
                    best = curr;
            }
            move_print(best);
        }
    }

    return 0;
}
