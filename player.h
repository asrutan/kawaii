// player.h
// Alex Rutan
// 11/21/15

#ifndef PLAYER_EXIST
#define PLAYER_EXIST

#include "movement.h"
#include "collideBox.h"

class Player
{
    private:
        Movement movement;
	collideBox cBox;
	int speed;
	bool airbound;
	bool xCollided;
	bool yCollided;
	//bool jumpReady;
	int yVelocity;
	int jumpStrength;
	int xNew;
	int ground;

    public:
        Player();
        ~Player();
        void tryMove();
	void move();
        void update();
	int getNewX();
	void fall();
	collideBox getCollideBox();
	void checkBottom();
	void setXCollided(bool);
	void setYCollided(bool);
	void setGround(int);
	void setYVelocity(int);
	bool quit;
        int x; // CHANGE THESE VALUES BACK TO PRIVATE
        int y; // THIS IS JUST TO TEST MOVING THE SPRITE IN Game!!!
	int height; //
	int frame; //animation frame TEST
	int tick; //for animation frame TEST
}; //end Player

#endif //PLAYER_EXISTS
