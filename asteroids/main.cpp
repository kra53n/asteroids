#include "game.h"

int main(int argc, char* argv[])
{
    init();

    Game game;
    GameInit(game);
    GameLoop(game);

    deInit(0);
    return 0;
}