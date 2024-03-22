#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

#include <SDL3/SDL.h>

namespace gg {
class Texture {
private:
    SDL_Texture* texture;

public:
    Texture(const std::string& path);
    ~Texture();
};
}  // namespace gg

#endif  // TEXTURE_H