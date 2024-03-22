#include "gg2/renderer.h"

#include "gg2/window.h"
#include "spdlog/spdlog.h"

namespace gg {
Renderer::Renderer(const Window& window) {
    renderer = SDL_CreateRenderer(static_cast<SDL_Window*>(window.getWindowHandle()), NULL,
                                  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        spdlog::critical("Failed to create renderer! Error: %s", SDL_GetError());
        return;
    }

    spdlog::debug("Renderer successfully created");
}

Renderer::~Renderer() {
    if (renderer != NULL) {
        SDL_DestroyRenderer(renderer);
        spdlog::debug("Renderer successfully destroyed");
    }
}
}  // namespace gg
