#include "gg2/game.h"

int main() {
    gg::Game* game = new gg::Game();

    game->initialize();

    game->uninitialize();

    return 0;
}