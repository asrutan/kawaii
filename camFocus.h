// camFocus.h
// Alex Rutan
// 12/1/15

#ifndef CAMFOCUS_EXIST
#define CAMFOCUS_EXIST

#include "player.h"
#include "enemy.h"
#include "world.h"

class camFocus
{
    private:
        Player* player;
	Enemy* enemy;
        World* world;
        int xTarget;
	int yTarget;
	int xVelocity;
	int yVelocity;
	bool campan;

    public:
        camFocus();
	camFocus(Player*, Enemy*, World*);
	~camFocus();
	void update();
	void move();
        int x;
	int y;
	//bool init();
	//	bool loadTextures();
};

#endif

