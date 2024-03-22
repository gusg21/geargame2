#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

#include <SDL3/SDL.h>

namespace gg {
class Renderer;

class Texture {
private:
    SDL_Texture* texture;

public:
    Texture(const gg::Renderer& renderer, const std::string& path);
    ~Texture();

    bool isOk() const { return texture != NULL; };
};
}  // namespace gg

#endif  // TEXTURE_H