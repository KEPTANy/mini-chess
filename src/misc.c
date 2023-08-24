#include "mini_chess.h"

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

void mini_chess_init() {
    random_init(time(NULL));

    attacks_init();
    position_init();
}

Move str_to_move(char *str) {
    Piece promoted;
    bool is_promo = true;
    switch (str[4]) {
    case 'n': promoted = P_WHITE_KNIGHT; break;
    case 'b': promoted = P_WHITE_BISHOP; break;
    case 'r': promoted = P_WHITE_ROOK;   break;
    case 'q': promoted = P_WHITE_QUEEN;  break;
    default: is_promo = false;
    }
    return move_create(square_create(str[0] - 'a', str[1] - '1'), square_create(str[2] - 'a', str[3] - '1'), 0, promoted, 0, is_promo, 0);
}

void print_move(Move move) {
    const char files[] = "abcde";
    const char ranks[] = "123456";
    Square src = move_get_source(move);
    Square trg = move_get_target(move);
    printf("%c%c%c%c", files[square_get_file(src)], ranks[square_get_rank(src)], files[square_get_file(trg)], ranks[square_get_rank(trg)]);
    if (move_is_promotion(move))
        printf("%c", piece_type_to_char(piece_get_type(move_get_promoted_piece(move))));
    printf("\n");
}

void main_loop() {
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    
    char input[2048];
    Position position;
    MoveList list;

    printf("ready\n");

    while (1) {
        fflush(stdout);
        memset(input, 0, sizeof(input) * sizeof(char));

        if (!fgets(input, 2048, stdin))
            continue;

        if (input[0] == '\n')
            continue;

        if (strncmp(input, "position", 8) == 0) {
            position_set(&position, input + 9);

            print_move(pv_line.list[pv_line.size - 1]);
        } else if (strncmp(input, "apply", 5) == 0) {
            Move move = str_to_move(input + 6);
            movegen(&position, &list, false);

            bool is_legal = false;
            for (int i = 0; i < list.size; i++) {
                if ((list.list[i] & 0b00000000010000111100001111111111) == move) {
                    is_legal = true;
                    break;
                }
            }

            if (is_legal)
                position_apply(&position, move);
        } else if (strncmp(input, "search", 6) == 0) {
            search(&position, atoi(input + 7));
        } else if (strncmp(input, "quit", 4) == 0) {
            break;
        }
    }
}
