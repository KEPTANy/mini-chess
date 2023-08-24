#include "mini_chess.h"

static uint32_t random_seed;

void random_init(uint32_t seed) {
    random_seed = seed;
}

uint32_t random32() {
    random_seed ^= random_seed << 13;
    random_seed ^= random_seed >> 17;
    random_seed ^= random_seed << 5;
    return random_seed;
}

uint64_t random64() {
    return ((uint64_t)(random32()) & 0xFFFF)         |
           (((uint64_t)(random32()) & 0xFFFF) << 16) |
           (((uint64_t)(random32()) & 0xFFFF) << 32) |
           (((uint64_t)(random32()) & 0xFFFF) << 48);
}