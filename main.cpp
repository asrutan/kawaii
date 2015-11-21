//main.cpp
#include <iostream>
#include "game.h"

using namespace std;

/*
  Calls an instance of game
  Initializes SDL stuff
  Runs the main game loop
  When the loop is over, safely close SDL
 */
int main()
{
    Game game;
    game.init();
    game.run();
    game.close();
    
    return 0;
} //end main
