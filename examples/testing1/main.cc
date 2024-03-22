#include "gg2/game.h"

int main() {
    gg::Game* game = new gg::Game();
    if (game->initialize() != gg::Game::GameError::SUCCESS) {
        return 1;
    }

    game->doLoop();

    game->uninitialize();
    return 0;
}