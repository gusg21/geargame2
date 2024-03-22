#ifndef WINDOW_H
#define WINDOW_H

#include <string>

#include "SDL3/SDL.h"

namespace gg {
class Renderer;

class Window {
private:
    gg::Renderer* renderer;
    
    SDL_Window* window;

public:
    Window(const std::string& title, uint32_t width, uint32_t height);
    ~Window();

    bool isOk() const { return window != NULL; };

    void* getWindowHandle() const { return static_cast<void*>(window); };
};  // class Window
}  // namespace gg

#endif  // WINDOW_H