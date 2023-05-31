#include <stdio.h>
#include <stdlib.h>

#include "../src/mini_chess.h"

#define ASSERT(expr) do { if (!(expr)) { printf("Test \"%s\" failed at line %d\n", __func__, __LINE__); exit(1); } } while (0)

void test_color() {
    ASSERT(color_inverse(C_WHITE) == C_BLACK);
    ASSERT(color_inverse(C_BLACK) == C_WHITE);
}

void test_piece() {
    ASSERT(piece_create(C_WHITE, PT_PAWN  ) == P_WHITE_PAWN  );
    ASSERT(piece_create(C_WHITE, PT_KNIGHT) == P_WHITE_KNIGHT);
    ASSERT(piece_create(C_WHITE, PT_BISHOP) == P_WHITE_BISHOP);
    ASSERT(piece_create(C_WHITE, PT_ROOK  ) == P_WHITE_ROOK  );
    ASSERT(piece_create(C_WHITE, PT_QUEEN ) == P_WHITE_QUEEN );
    ASSERT(piece_create(C_WHITE, PT_KING  ) == P_WHITE_KING  );

    ASSERT(piece_create(C_BLACK, PT_PAWN  ) == P_BLACK_PAWN  );
    ASSERT(piece_create(C_BLACK, PT_KNIGHT) == P_BLACK_KNIGHT);
    ASSERT(piece_create(C_BLACK, PT_BISHOP) == P_BLACK_BISHOP);
    ASSERT(piece_create(C_BLACK, PT_ROOK  ) == P_BLACK_ROOK  );
    ASSERT(piece_create(C_BLACK, PT_QUEEN ) == P_BLACK_QUEEN );
    ASSERT(piece_create(C_BLACK, PT_KING  ) == P_BLACK_KING  );

    ASSERT(piece_get_color(P_WHITE_PAWN  ) == C_WHITE);
    ASSERT(piece_get_color(P_WHITE_KNIGHT) == C_WHITE);
    ASSERT(piece_get_color(P_WHITE_BISHOP) == C_WHITE);
    ASSERT(piece_get_color(P_WHITE_ROOK  ) == C_WHITE);
    ASSERT(piece_get_color(P_WHITE_QUEEN ) == C_WHITE);
    ASSERT(piece_get_color(P_WHITE_KING  ) == C_WHITE);

    ASSERT(piece_get_color(P_BLACK_PAWN  ) == C_BLACK);
    ASSERT(piece_get_color(P_BLACK_KNIGHT) == C_BLACK);
    ASSERT(piece_get_color(P_BLACK_BISHOP) == C_BLACK);
    ASSERT(piece_get_color(P_BLACK_ROOK  ) == C_BLACK);
    ASSERT(piece_get_color(P_BLACK_QUEEN ) == C_BLACK);
    ASSERT(piece_get_color(P_BLACK_KING  ) == C_BLACK);

    ASSERT(piece_get_type(P_WHITE_PAWN) == PT_PAWN);
    ASSERT(piece_get_type(P_BLACK_PAWN) == PT_PAWN);

    ASSERT(piece_get_type(P_WHITE_KNIGHT) == PT_KNIGHT);
    ASSERT(piece_get_type(P_BLACK_KNIGHT) == PT_KNIGHT);

    ASSERT(piece_get_type(P_WHITE_BISHOP) == PT_BISHOP);
    ASSERT(piece_get_type(P_BLACK_BISHOP) == PT_BISHOP);

    ASSERT(piece_get_type(P_WHITE_ROOK) == PT_ROOK);
    ASSERT(piece_get_type(P_BLACK_ROOK) == PT_ROOK);

    ASSERT(piece_get_type(P_WHITE_QUEEN) == PT_QUEEN);
    ASSERT(piece_get_type(P_BLACK_QUEEN) == PT_QUEEN);

    ASSERT(piece_get_type(P_WHITE_KING) == PT_KING);
    ASSERT(piece_get_type(P_BLACK_KING) == PT_KING);

}

int main() {
    test_color();
    test_piece();

    puts("All tests passed");
    return 0;
}
