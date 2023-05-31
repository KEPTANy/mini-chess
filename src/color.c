#include "mini_chess.h"

Color color_inverse(Color color) {
    return color == C_WHITE ? C_BLACK : C_WHITE;
}
