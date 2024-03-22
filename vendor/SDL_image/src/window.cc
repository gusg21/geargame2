#include "gg2/window.h"

#include "SDL3/SDL.h"
#include "spdlog/spdlog.h"

#include "gg2/renderer.h"

namespace gg {

Window::Window(const std::string &title, uint32_t width, uint32_t height) {
    window = SDL_CreateWindow(title.c_str(), width, height, 0);
    if (window == NULL) {
        spdlog::critical("Failed to create window! Error: %s", SDL_GetError());
        return;
    }

    spdlog::debug("Window successfully created");
}

Window::~Window() {
    if (window != NULL) {
        SDL_DestroyWindow(window);
        spdlog::debug("Window successfully destroyed");
    }
};

}  // namespace gg