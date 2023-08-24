#include "mini_chess.h"

int32_t popcnt32(uint32_t n) {
    return __builtin_popcount(n);
}

int32_t popcnt64(uint64_t n) {
    return __builtin_popcountll(n);
}

int32_t lsb32(uint32_t n) {
    return __builtin_ctz(n);
}

int32_t lsb64(uint64_t n) {
    return __builtin_ctzll(n);
}

int32_t msb32(uint32_t n) {
    return 31 - __builtin_clz(n);
}

int32_t msb64(uint64_t n) {
    return 63 - __builtin_clzll(n);
}

int32_t pop_lsb64(uint64_t *n) {
    int32_t res = lsb64(*n);
    *n &= *n - 1;
    return res;
}

int32_t pop_lsb32(uint32_t *n) {
    int32_t res = lsb32(*n);
    *n &= *n - 1;
    return res;
}
