#include "mini_chess.h"

Bitboard direction_shift(Bitboard bitboard, Direction direction) {
    return (direction > 0) ? (bitboard << direction) : (bitboard >> (-direction));
}
