// enemy.h
// Alex Rutan
// 1/3/16

#ifndef ENEMY_EXIST
#define ENEMY_EXIST

#include "collideBox.h"
#include "entity.h"

class Enemy : public Entity
{
    private:
	int jumpStrength;

    public:
        Enemy();
        ~Enemy();
        void tryMove();
	void move();
        void update();
	void fall();
	void checkBottom();
	bool left;
	bool right;
	int frame; //animation frame TEST
	int tick; //for animation frame TEST
}; //end Enemy

#endif //ENEMY_EXISTS
