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

void test_square() {
    ASSERT(square_create(F_A, R_1) == S_A1);
    ASSERT(square_create(F_B, R_1) == S_B1);
    ASSERT(square_create(F_C, R_1) == S_C1);
    ASSERT(square_create(F_D, R_1) == S_D1);
    ASSERT(square_create(F_E, R_1) == S_E1);
    ASSERT(square_create(F_A, R_2) == S_A2);
    ASSERT(square_create(F_B, R_2) == S_B2);
    ASSERT(square_create(F_C, R_2) == S_C2);
    ASSERT(square_create(F_D, R_2) == S_D2);
    ASSERT(square_create(F_E, R_2) == S_E2);
    ASSERT(square_create(F_A, R_3) == S_A3);
    ASSERT(square_create(F_B, R_3) == S_B3);
    ASSERT(square_create(F_C, R_3) == S_C3);
    ASSERT(square_create(F_D, R_3) == S_D3);
    ASSERT(square_create(F_E, R_3) == S_E3);
    ASSERT(square_create(F_A, R_4) == S_A4);
    ASSERT(square_create(F_B, R_4) == S_B4);
    ASSERT(square_create(F_C, R_4) == S_C4);
    ASSERT(square_create(F_D, R_4) == S_D4);
    ASSERT(square_create(F_E, R_4) == S_E4);
    ASSERT(square_create(F_A, R_5) == S_A5);
    ASSERT(square_create(F_B, R_5) == S_B5);
    ASSERT(square_create(F_C, R_5) == S_C5);
    ASSERT(square_create(F_D, R_5) == S_D5);
    ASSERT(square_create(F_E, R_5) == S_E5);
    ASSERT(square_create(F_A, R_6) == S_A6);
    ASSERT(square_create(F_B, R_6) == S_B6);
    ASSERT(square_create(F_C, R_6) == S_C6);
    ASSERT(square_create(F_D, R_6) == S_D6);
    ASSERT(square_create(F_E, R_6) == S_E6);

    ASSERT(square_get_rank(S_A1) == R_1);
    ASSERT(square_get_rank(S_B1) == R_1);
    ASSERT(square_get_rank(S_C1) == R_1);
    ASSERT(square_get_rank(S_D1) == R_1);
    ASSERT(square_get_rank(S_E1) == R_1);
    ASSERT(square_get_rank(S_A2) == R_2);
    ASSERT(square_get_rank(S_B2) == R_2);
    ASSERT(square_get_rank(S_C2) == R_2);
    ASSERT(square_get_rank(S_D2) == R_2);
    ASSERT(square_get_rank(S_E2) == R_2);
    ASSERT(square_get_rank(S_A3) == R_3);
    ASSERT(square_get_rank(S_B3) == R_3);
    ASSERT(square_get_rank(S_C3) == R_3);
    ASSERT(square_get_rank(S_D3) == R_3);
    ASSERT(square_get_rank(S_E3) == R_3);
    ASSERT(square_get_rank(S_A4) == R_4);
    ASSERT(square_get_rank(S_B4) == R_4);
    ASSERT(square_get_rank(S_C4) == R_4);
    ASSERT(square_get_rank(S_D4) == R_4);
    ASSERT(square_get_rank(S_E4) == R_4);
    ASSERT(square_get_rank(S_A5) == R_5);
    ASSERT(square_get_rank(S_B5) == R_5);
    ASSERT(square_get_rank(S_C5) == R_5);
    ASSERT(square_get_rank(S_D5) == R_5);
    ASSERT(square_get_rank(S_E5) == R_5);
    ASSERT(square_get_rank(S_A6) == R_6);
    ASSERT(square_get_rank(S_B6) == R_6);
    ASSERT(square_get_rank(S_C6) == R_6);
    ASSERT(square_get_rank(S_D6) == R_6);
    ASSERT(square_get_rank(S_E6) == R_6);

    ASSERT(square_get_file(S_A1) == F_A);
    ASSERT(square_get_file(S_B1) == F_B);
    ASSERT(square_get_file(S_C1) == F_C);
    ASSERT(square_get_file(S_D1) == F_D);
    ASSERT(square_get_file(S_E1) == F_E);
    ASSERT(square_get_file(S_A2) == F_A);
    ASSERT(square_get_file(S_B2) == F_B);
    ASSERT(square_get_file(S_C2) == F_C);
    ASSERT(square_get_file(S_D2) == F_D);
    ASSERT(square_get_file(S_E2) == F_E);
    ASSERT(square_get_file(S_A3) == F_A);
    ASSERT(square_get_file(S_B3) == F_B);
    ASSERT(square_get_file(S_C3) == F_C);
    ASSERT(square_get_file(S_D3) == F_D);
    ASSERT(square_get_file(S_E3) == F_E);
    ASSERT(square_get_file(S_A4) == F_A);
    ASSERT(square_get_file(S_B4) == F_B);
    ASSERT(square_get_file(S_C4) == F_C);
    ASSERT(square_get_file(S_D4) == F_D);
    ASSERT(square_get_file(S_E4) == F_E);
    ASSERT(square_get_file(S_A5) == F_A);
    ASSERT(square_get_file(S_B5) == F_B);
    ASSERT(square_get_file(S_C5) == F_C);
    ASSERT(square_get_file(S_D5) == F_D);
    ASSERT(square_get_file(S_E5) == F_E);
    ASSERT(square_get_file(S_A6) == F_A);
    ASSERT(square_get_file(S_B6) == F_B);
    ASSERT(square_get_file(S_C6) == F_C);
    ASSERT(square_get_file(S_D6) == F_D);
    ASSERT(square_get_file(S_E6) == F_E);

    ASSERT(square_distance(S_A1, S_E6) == square_distance(S_E6, S_A1));
    ASSERT(square_distance(S_A1, S_E6) == 5);
    ASSERT(square_distance(S_A1, S_A1) == 0);
    ASSERT(square_distance(S_E6, S_E5) == 1);
    ASSERT(square_distance(S_E6, S_D6) == 1);
}

void test_bitboard() {
    ASSERT(bitboard_of_file(F_A) == BB_FILE_A);
    ASSERT(bitboard_of_file(F_B) == BB_FILE_B);
    ASSERT(bitboard_of_file(F_C) == BB_FILE_C);
    ASSERT(bitboard_of_file(F_D) == BB_FILE_D);
    ASSERT(bitboard_of_file(F_E) == BB_FILE_E);

    ASSERT(bitboard_of_rank(R_1) == BB_RANK_1);
    ASSERT(bitboard_of_rank(R_2) == BB_RANK_2);
    ASSERT(bitboard_of_rank(R_3) == BB_RANK_3);
    ASSERT(bitboard_of_rank(R_4) == BB_RANK_4);
    ASSERT(bitboard_of_rank(R_5) == BB_RANK_5);
    ASSERT(bitboard_of_rank(R_6) == BB_RANK_6);

    for (Square s = S_A1; s < SQUARE_NUM; s++) {
        Bitboard bb_sqr  = bitboard_of_square(s),
                 bb_file = bitboard_of_file(square_get_file(s)),
                 bb_rank = bitboard_of_rank(square_get_rank(s));
        ASSERT(bb_sqr == (bb_file & bb_rank));
    }
}

void test_direction() {
    ASSERT(direction_shift(BB_RANK_1, D_N) == BB_RANK_2);
    ASSERT(direction_shift(BB_RANK_2, D_S) == BB_RANK_1);
    ASSERT(direction_shift(BB_FILE_B, D_E) == BB_FILE_C);
    ASSERT(direction_shift(BB_FILE_D, D_W) == BB_FILE_C);
}

void test_attacks() {
    // Pawns

    // . . . . .
    // . . . . .
    // . . . . .
    // . x . . .
    // P . . . .
    // . . . . .
    ASSERT((attacks_pawn(S_A2, C_WHITE) & BB_ALL_SQUARES) == 2048);

    // . . . . .
    // . . . p .
    // . . x . x
    // . . . . .
    // . . . . .
    // . . . . .
    ASSERT((attacks_pawn(S_D5, C_BLACK) & BB_ALL_SQUARES) == 655360);

    // . . . . .
    // x . x . .
    // .(P). x .
    // . x P x .
    // P . . . P
    // . . . . .
    ASSERT((attacks_pawns(70176, C_WHITE) & BB_ALL_SQUARES) == 5580800);

    // . . . . .
    // p p p p p
    // x x x x x
    // . . . . .
    // . . . . .
    // . . . . .
    ASSERT((attacks_pawns(32505856, C_BLACK) & BB_ALL_SQUARES) == 1015808);

    // Knights

    // . . . . .
    // . x . x .
    // x . . . x
    // . . N . .
    // x . . . x
    // . x . x .
    ASSERT((attacks_knight(S_C3) & BB_ALL_SQUARES) == 11043370);

    // . . . . .
    // . . . . .
    // . . . . .
    // . x . . .
    // . . x . .
    // N . . . .
    ASSERT((attacks_knight(S_A1) & BB_ALL_SQUARES) == 2176);

    // . . . . .
    // . . . . .
    // x x x x x
    // x x x x x
    // N N N N N
    // x x x x x
    ASSERT((attacks_knights(992) & BB_ALL_SQUARES) == 1047583);

    // . . . x .
    // . N x . .
    // . x . x N
    // x . x . x
    // . . N x .
    // x . . . x
    ASSERT((attacks_knights(2621568) & BB_ALL_SQUARES) == 272979217);

    // Bishops

    // . . . x .
    // x . x . .
    // . B . . .
    // x . x . .
    // . . . x .
    // . . . . x
    ASSERT((attacks_bishop(S_B4, 65536) & BB_ALL_SQUARES) == 273683728);

    // . . . K .
    // x . . . .
    // . x .(P).
    // . . B . .
    // k x .(r).
    // x n . . .
    ASSERT((attacks_bishop(S_C3, 268701986) & BB_ALL_SQUARES) == 1376577);

    // x x x x r
    // . B B . .
    // x x x x .
    // x . .(p)x
    // . . . k .
    // K . . . .
    ASSERT((attacks_bishops(6291456, 543170817) & BB_ALL_SQUARES) == 503833600);

    // . . . . x
    // . . . x .
    // x . x . .
    // .(B). . .
    // x . x . x
    // . . .(B).
    ASSERT((attacks_bishops(2056, 2056) & BB_ALL_SQUARES) == 545426088);

    // Rooks

    // . . . . .
    // . . . . .
    //(p). . . .
    // x . . . .
    // x . . . .
    // R x(n). .
    ASSERT((attacks_rook(S_A1, 32773) & BB_ALL_SQUARES) == 33830);

    // . . x . .
    // . . x . .
    // x x R x x
    // . . x . .
    // . . x . .
    // . . x . .
    ASSERT((attacks_rook(S_C4, 131072) & BB_ALL_SQUARES) == 139300996);

    // . x x . .
    // . x x . .
    // x x R x x
    // . x x . .
    // x R x x x
    // . x x . .
    ASSERT((attacks_rooks(131136, 131136) & BB_ALL_SQUARES) == 208509862);

    // . . . . .
    // . . . . .
    // . .(p). .
    // x x(R)x x
    // x x(R)x(p)
    // . . x . .
    ASSERT((attacks_rooks(4224, 135808) & BB_ALL_SQUARES) == 163812);

    // Queens

    // x . x . x
    // . x x x .
    // x x Q x x
    // . x x x .
    // x . x . x
    // . . x . .
    ASSERT((attacks_queen(S_C4, 131072) & BB_ALL_SQUARES) == 720222884);

    // . . x . x
    // .(r)x x .
    // x x Q(p).
    // . x x x .
    //(N). x . x
    // . . x . .
    ASSERT((attacks_queen(S_C4, 2490400) & BB_ALL_SQUARES) == 686144164);

    // . x x x .
    // x x Q x x
    // . x x x .
    // x x x . x
    // x Q x x x
    // x x x . .
    ASSERT((attacks_queens(4194368, 4194368) & BB_ALL_SQUARES) == 498556839);

    // . . . . .
    // . . . . .
    //(r). . . .
    // x .(n).(p)
    // x x . x x
    //(Q)x x x(Q)
    ASSERT((attacks_queens(17, 53265) & BB_ALL_SQUARES) == 55167);

    // Kings

    // . . . . .
    // . . . . .
    // x x . . .
    // K x . . .
    // x x . . .
    // . . . . .
    ASSERT((attacks_king(S_A3) & BB_ALL_SQUARES) == 100448);

    // . . . . .
    // . . . . .
    // . . . . .
    // . . . . .
    // . . . x x
    // . . . x K
    ASSERT((attacks_king(S_E1) & BB_ALL_SQUARES) == 776);

    // . . . . .
    // . x x x .
    // . x K x .
    // . x x x .
    // . . . x x
    // . . . x K
    ASSERT((attacks_kings(131088) & BB_ALL_SQUARES) == 15022856);

    // . . . . .
    // . . . . .
    // . . . . .
    // . . . . .
    // x x . x x
    // K x . x K
    ASSERT((attacks_kings(17) & BB_ALL_SQUARES) == 874);
}

int main() {
    attacks_init();

    test_color();
    test_piece();
    test_square();
    test_bitboard();
    test_direction();
    test_attacks();

    puts("All tests passed");
    return 0;
}
