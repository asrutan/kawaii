// player.h
// Alex Rutan
// 11/21/15

#ifndef PLAYER_EXIST
#define PLAYER_EXIST

#include "movement.h"
#include "collideBox.h"
#include "entity.h"

class Player : public Entity
{
    private:
        Movement movement;
	int jumpStrength;
	collideBox aBox;
	bool attack;
	int attackCountUp;
	int attackCountDown;
	char lastMove;

    public:
        Player();
        ~Player();
        void tryMove();
	void move();
        void update();
	void fall();
	int getXCollided();
	bool attackCheck();
	void attackAction(Entity*);
	void checkBottom();
	void hit();
	bool animForward;
	bool animBackward;
	bool animIdle;
	bool quit;
	int frame; //animation frame TEST
	int tick; //for animation frame TEST
}; //end Player

#endif //PLAYER_EXISTS
