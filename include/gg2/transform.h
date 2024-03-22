#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "gg2/vector.h"

namespace gg {
class Transform {
public:
    Vec2 pos;
    Vec2 scale;
    float rotation;
}
}  // namespace gg

#endif  // TRANSFORM_H