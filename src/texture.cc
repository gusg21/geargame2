#include "gg2/texture.h"

#include "SDL3/SDL.h"
#include "SDL3_image/SDL_image.h"
#include "spdlog/spdlog.h"

#include "gg2/renderer.h"

namespace gg {
Texture::Texture(const gg::Renderer& renderer, const std::string& path) {
    texture = IMG_LoadTexture(static_cast<SDL_Renderer*>(renderer.getRendererHandle()), path.c_str());
    if (texture == NULL) {
        spdlog::warn("Failed to load texture {}!", path.c_str());
    } else {
        spdlog::info("Loaded texture {} successfully", path.c_str());
    }
}

Texture::~Texture() {
    SDL_DestroyTexture(texture);
}
}  // namespace gg

