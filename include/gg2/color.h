#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>

namespace gg {
class Color {
public:
    uint8_t r, g, b, a;

    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : r(r), g(g), b(b), a(a) {}
};
}  // namespace gg

#endif  // COLOR_H