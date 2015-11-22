// player.h
// Alex Rutan
// 11/21/15

#ifndef PLAYER_EXIST
#define PLAYER_EXIST

#include "movement.h"
#include "world.h"

class Player
{
    private:
        Movement movement;
	World world;
	int speed;
	bool airbound;
	//bool jumpReady;
	int yVelocity;

    public:
        Player();
        ~Player();
        void move();
        void update();
	void fall();
	void checkBottom(int);
	bool quit;
        int x; // CHANGE THESE VALUES BACK TO PRIVATE
        int y; // THIS IS JUST TO TEST MOVING THE SPRITE IN Game!!!
	int height; //
}; //end Player

#endif //PLAYER_EXISTS
