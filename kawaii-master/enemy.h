// enemy.h
// Alex Rutan
// 1/3/16

#ifndef ENEMY_EXIST
#define ENEMY_EXIST

#include "collideBox.h"

class Enemy
{
    private:
	collideBox cBox;
	int speed;
	bool airbound;
	bool xCollided;
	bool yCollided;
	int yVelocity;
	int xVelocity;
	int jumpStrength;
	int xNew;
	int ground;

    public:
        Enemy();
        ~Enemy();
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
        int x; // CHANGE THESE VALUES BACK TO PRIVATE
        int y; // THIS IS JUST TO TEST MOVING THE SPRITE IN Game!!!
	int height; //
	int frame; //animation frame TEST
	int tick; //for animation frame TEST
}; //end Enemy

#endif //ENEMY_EXISTS
