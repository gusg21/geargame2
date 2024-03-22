#include "gg2/game.h"

#include <stdint.h>

#include <cassert>

#include "SDL3/SDL.h"
#include "spdlog/spdlog.h"

#include "gg2/window.h"
#include "gg2/renderer.h"
#include "gg2/game.h"

namespace gg {

Game::Game() : initialized(false) {}

Game::~Game() {
    if (!initialized) uninitialize();
}

Game::GameError Game::initialize() {
    // Initialize the logger
    spdlog::set_level(spdlog::level::debug);

    // Ensure we're not already initialized
    assert(!initialized);

    // Initialize SDL
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS |
                 SDL_INIT_TIMER)) {
        spdlog::critical("SDL Failed to initialize!\nError: %s",
                         SDL_GetError());
        return GameError::SDL_FAIL;
    }
    spdlog::debug("SDL Initialized");

    // Create a window
    window = new gg::Window("geargame2", 640, 480);

    // Create a renderer
    renderer = new gg::Renderer(*window);

    // Success!
    initialized = true;
    spdlog::debug("Geargame Initialized");
    return GameError::SUCCESS;
}



void Game::uninitialize() {
    // Ensure we were previously initialized
    assert(initialized);

    // Delete the renderer
    delete renderer;

    // Delete the window
    delete window;

    // Quit SDL
    SDL_Quit();
    initialized = false;
    spdlog::debug("SDL Uninitialized");

    // Success!
    spdlog::debug("Geargame Uninitialized");
}

void Game::doLoop() {
    spdlog::debug("Beginning game loop...");

    running = true;
    SDL_Event event;
    while (running) {
        // Poll the event queue
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT:
                    running = false;
                    break;
            }
        }

        // Rest of the stuff lol
    }

    spdlog::debug("Exiting game loop...");
}
}  // namespace gg
