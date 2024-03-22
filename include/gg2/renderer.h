#ifndef RENDERER_H
#define RENDERER_H

#include "SDL3/SDL.h"

#include "gg2/color.h"

namespace gg {
class Window;
class Texture;

class Renderer {
private:
    SDL_Renderer* renderer;
    gg::Color clearColor;

public:
    Renderer(const gg::Window& window);
    Renderer(const gg::Texture& texture);
    ~Renderer();

    bool isOk() const { return renderer != NULL; };

    void* getRendererHandle() const { return static_cast<void*>(renderer); };

    void setClearColor(gg::Color color);
    void clear();
    void present();
};  // class Renderer
}  // namespace gg

#endif  // RENDERER_H