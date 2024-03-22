#include "gg2/renderer.h"

#include "gg2/window.h"
#include "spdlog/spdlog.h"

namespace gg {
Renderer::Renderer(const Window& window) : clearColor((gg::Color){31, 25, 46, 255}) {
    renderer = SDL_CreateRenderer(static_cast<SDL_Window*>(window.getWindowHandle()), NULL,
                                  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!isOk()) {
        spdlog::critical("Failed to create renderer! Error: {}", SDL_GetError());
        return;
    }

    spdlog::debug("Renderer successfully created");
}

Renderer::~Renderer() {
    if (isOk()) {
        SDL_DestroyRenderer(renderer);
        spdlog::debug("Renderer successfully destroyed");
    }
}

void Renderer::setClearColor(gg::Color color) { clearColor = color; }

void Renderer::clear() {
    if (isOk()) {
        SDL_SetRenderDrawColor(renderer, clearColor.r, clearColor.g, clearColor.b, clearColor.a);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    }
}

void Renderer::present() {
    if (isOk()) {
        SDL_RenderPresent(renderer);
    }
}

}  // namespace gg
