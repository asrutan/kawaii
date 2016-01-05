// collision.cpp
// PA
// 12/01/15

#include <iostream>
#include "player.h"
#include "enemy.h"
#include "world.h"
#include "collision.h"
#include "collideBox.h"
#include "entity.h"

using namespace std;

Collision::Collision()
{
    *player = Player();
    *enemy = Enemy();
    *world = World();
}

Collision::Collision(Player* p, Enemy* e, World* w)
{
    player = p;
    enemy = e;
    world = w;
}

Collision::Collision(World* w)
{
    world = w;
}

Collision::~Collision()
{

}

void Collision::playerWallCollision(Entity* e)
{
    bool returnVal = false;
    for(int i = 0; i < world->getTileCount(); i++)
    {
	if(e->getCollideBox()->getX1() < world->getIthTile(i)->getCollideBox().getX2() && e->getCollideBox()->getX2() > world->getIthTile(i)->getCollideBox().getX1())//Collide from left
	{//if outside of given x tile
	    //cout << "true" << endl;
	    if(e->getCollideBox()->getY1() > world->getIthTile(i)->getCollideBox().getY1() && e->getCollideBox()->getY1() < world->getIthTile(i)->getCollideBox().getY2())
	    {//only top part of player is colliding
		returnVal = true;
	    }
	    if(world->getIthTile(i)->getCollideBox().getY1() > e->getCollideBox()->getY1() && world->getIthTile(i)->getCollideBox().getY2() < e->getCollideBox()->getY2())
	    {//tile is in middle of player
		returnVal = true;
	    }
	    if(e->getCollideBox()->getY2() > world->getIthTile(i)->getCollideBox().getY1() && e->getCollideBox()->getY2() <= world->getIthTile(i)->getCollideBox().getY2())
	    {//only bottom part of player is colliding
		returnVal = true;
	    }
	}
    }//end for
    if(returnVal)
    {
	e->setXVelocity(0);
    }
    e->setXCollided(returnVal);
}

void Collision::checkFloorCollision(Entity* e)
{
    bool returnVal = false;
    //int returnVal = 800;
    for(int i = 0; i < world->getTileCount(); i++)
    {
        if((e->getCollideBox()->getX1() < world->getIthTile(i)->getCollideBox().getX2() && e->getCollideBox()->getX1() > world->getIthTile(i)->getCollideBox().getX1()) || (e->getCollideBox()->getX2() > world->getIthTile(i)->getCollideBox().getX1() && e->getCollideBox()->getX2() < world->getIthTile(i)->getCollideBox().getX2()) || (e->getCollideBox()->getX1() > world->getIthTile(i)->getCollideBox().getX1() && e->getCollideBox()->getX2() < world->getIthTile(i)->getCollideBox().getX2()))
        {//if inside of given x tile
	    //cout << "in outter if" << endl;
	    if((e->getCollideBox()->getY2() >= world->getIthTile(i)->getCollideBox().getY1() && e->getCollideBox()->getY1() <= world->getIthTile(i)->getCollideBox().getY1()))
	    {//if touching tile from above
		e->y = world->getIthTile(i)->getCollideBox().getY1() - e->height;
		//cout << e->y << endl;
		returnVal = true;
		//cout << "Touching tile from Above" << endl;
	    }
	    if((e->getCollideBox()->getY1() <= world->getIthTile(i)->getCollideBox().getY2() && e->getCollideBox()->getY2() >= world->getIthTile(i)->getCollideBox().getY2()))
	    {//if touching tile from below
		e->y = world->getIthTile(i)->getCollideBox().getY2() + 1;
		e->setYVelocity(0);
		//returnVal = true;
	    }
	}
	//player->setGround(returnVal);
    }
    e->setYCollided(returnVal);
}


