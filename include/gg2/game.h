#ifndef GAME_H
#define GAME_H

namespace gg {
class Game {
private:
    bool initialized;

public:
    enum GameError {
        SUCCESS,
        SDL_FAIL
    };

    Game();
    ~Game();

    GameError initialize();
    void uninitialize();
};
} // namespace gg

#endif // GAME_H