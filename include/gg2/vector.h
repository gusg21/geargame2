#ifndef VECTOR_H
#define VECTOR_H

namespace gg
{
    class Vec2 {
    public:
        float x, y;

        Vec2() : x(0.f), y(0.f) {}
        Vec2(float x, float y) : x(x), y(y) {}
    }
} // namespace gg


#endif  // VECTOR_H