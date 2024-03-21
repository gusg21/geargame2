#include "gg2/game.h"

#include <stdint.h>

#include <cassert>

#include "SDL3/SDL.h"

namespace gg {
Game::Game() : initialized(false) {}

Game::~Game() {}

Game::GameError Game::initialize() {
    // Ensure we're not already initialized
    assert(!initialized);

    // Initialize SDL   
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER)) {
        return SDL_FAIL;
    }
}

void Game::uninitialize() {
    // Ensure we were previously initialized
    assert(initialized);

    // Quit SDL
    SDL_Quit();
}
} // namespace gg
