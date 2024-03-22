#ifndef GAME_H
#define GAME_H

#include "gg2/window.h"

namespace gg {
class Game {
private:
    bool initialized;
    bool running;

    gg::Window* window;
    gg::Renderer* renderer;

public:
    enum class GameError {
        SUCCESS,
        SDL_FAIL
    };

    Game();
    ~Game();

    GameError initialize();
    void uninitialize();

    void doLoop();

    gg::Window* getWindow() const;
}; // class Game
} // namespace gg

#endif // GAME_H