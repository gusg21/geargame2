#ifndef GAME_H
#define GAME_H

namespace gg {
class Window;
class Renderer;

class Game {
private:
    bool initialized;
    bool running;

    gg::Window* window;
    gg::Renderer* renderer;

public:
    enum class GameError {
        SUCCESS,
        SDL_FAIL,
        SDL_IMAGE_FAIL,
        WINDOW_FAIL,
        RENDERER_FAIL,
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