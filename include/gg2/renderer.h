#ifndef RENDERER_H
#define RENDERER_H

#include "SDL3/SDL.h"

namespace gg {
class Window;

class Renderer {
private:
    SDL_Renderer* renderer;

public:
    Renderer(const gg::Window& window);
    Renderer();

    ~Renderer();
};  // class Renderer
}  // namespace gg

#endif  // RENDERER_H