#include "mini_chess.h"

// TODO: implement functions instead of using GCC builtin ones

int32_t popcnt64(uint64_t n) {
    return __builtin_popcountll(n);
}

int32_t popcnt32(uint32_t n) {
    return __builtin_popcount(n);
}

int32_t lsb(uint64_t n) {
    return __builtin_ctzll(n);
}

int32_t msb(uint64_t n) {
    return 63 ^ __builtin_clzll(n);
}

int32_t pop_lsb64(uint64_t *n) {
    int32_t res = lsb(*n);
    *n &= *n - 1;
    return res;
}

int32_t pop_lsb32(uint32_t *n) {
    int32_t res = lsb((uint32_t)(*n));
    *n &= *n - 1;
    return res;
}
