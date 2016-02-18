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
	int xCollided;
	bool yCollided;
	int yVelocity;
	int xVelocity;
	int xNew;
	int spriteX;
	int spriteY;

    public:
        Entity();
        ~Entity();
        virtual void tryMove();
	virtual void move();
        virtual void update();
	int getNewX();
	void fall();
	virtual void hit();
	collideBox* getCollideBox();
	void checkBottom();
	void setXCollided(int);
	void setYCollided(bool);
	void setYVelocity(int);
	void setXVelocity(int);
	void setX(int);
	void setY(int);	
        int x; // CHANGE THESE VALUES BACK TO PRIVATE
        int y; // THIS IS JUST TO TEST MOVING THE SPRITE IN Game!!!
	bool left;
	bool right;
	int height;
	int width;
}; //end Enemy

#endif //ENEMY_EXISTS
