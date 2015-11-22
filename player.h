// player.h
// Alex Rutan
// 11/21/15

#ifndef PLAYER_EXIST
#define PLAYER_EXIST

#include "movement.h"

class Player
{
    private:
        Movement movement;

    public:
        Player();
        ~Player();
        void move();
        void update();
	bool quit;
        int x; // CHANGE THESE VALUES BACK TO PRIVATE
        int y; // THIS IS JUST TO TEST MOVING THE SPRITE IN Game!!!
}; //end Player

#endif //PLAYER_EXISTS
