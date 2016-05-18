#include <iostream>
#include "Game.hpp"
#include <ncurses.h>

using namespace std;

int main(int argc, char **argv)
{
    Game game(argc, argv);
    game.run();
    return 0;
}
