// enemy.h
// Alex Rutan
// 1/3/16

#ifndef ENTITY_EXIST
#define ENTITY_EXIST

#include "collideBox.h"

class Entity
{
    protected:
	collideBox cBox;
	int speed;
	bool airbound;
	bool xCollided;
	bool yCollided;
	int yVelocity;
	int xVelocity;
	int xNew;

    public:
        Entity();
        ~Entity();
        void tryMove();
	void move();
        void update();
	int getNewX();
	void fall();
	collideBox* getCollideBox();
	void checkBottom();
	void setXCollided(bool);
	void setYCollided(bool);
	void setYVelocity(int);
	void setXVelocity(int);
	void setX(int);
	void setY(int);	
        int x; // CHANGE THESE VALUES BACK TO PRIVATE
        int y; // THIS IS JUST TO TEST MOVING THE SPRITE IN Game!!!
	bool left;
	bool right;
	int height; //
	int width;
}; //end Enemy

#endif //ENEMY_EXISTS
