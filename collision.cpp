// collision.cpp
// PA
// 12/01/15

#include <iostream>
#include "world.h"
#include "collision.h"
#include "collideBox.h"
#include "entity.h"

using namespace std;

Collision::Collision()
{
    *world = World();
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
    int returnVal = 0;
    for(int i = 0; i < world->getTileCount(); i++)
    {
	if(returnVal != 2)
	{
	    if(e->getCollideBox()->getX1() < world->getIthTile(i)->getCollideBox().getX2() && e->getCollideBox()->getX2() > world->getIthTile(i)->getCollideBox().getX1())//Collide from left
	    {//if outside of given x tile
		if(e->getCollideBox()->getY1() > world->getIthTile(i)->getCollideBox().getY1() && e->getCollideBox()->getY1() < world->getIthTile(i)->getCollideBox().getY2())
		{//only top part of player is colliding
		    returnVal = world->getIthTile(i)->getTag();
		}
		if(world->getIthTile(i)->getCollideBox().getY1() > e->getCollideBox()->getY1() && world->getIthTile(i)->getCollideBox().getY2() < e->getCollideBox()->getY2())
		{//tile is in middle of player
		    returnVal = world->getIthTile(i)->getTag();
		}
		if(e->getCollideBox()->getY2() > world->getIthTile(i)->getCollideBox().getY1() && e->getCollideBox()->getY2() <= world->getIthTile(i)->getCollideBox().getY2())
		{//only bottom part of player is colliding
		    returnVal = world->getIthTile(i)->getTag();
		}
	    }
	}
    }//end for
    if(returnVal != 0)
    {
	e->setXVelocity(0);
    }
    //cout << returnVal << endl;
    e->setXCollided(returnVal);
}

void Collision::checkFloorCollision(Entity* e)
{
    bool returnVal = false;
    for(int i = 0; i < world->getTileCount(); i++)//for each tile
    {
        if((e->getCollideBox()->getX1() < world->getIthTile(i)->getCollideBox().getX2() && e->getCollideBox()->getX1() > world->getIthTile(i)->getCollideBox().getX1()) 
	   || (e->getCollideBox()->getX2() > world->getIthTile(i)->getCollideBox().getX1() && e->getCollideBox()->getX2() < world->getIthTile(i)->getCollideBox().getX2()) 
	   || (e->getCollideBox()->getX1() > world->getIthTile(i)->getCollideBox().getX1() && e->getCollideBox()->getX2() < world->getIthTile(i)->getCollideBox().getX2()))
        {//if inside of given x tile
	    if((e->getCollideBox()->getY2() >= world->getIthTile(i)->getCollideBox().getY1() && e->getCollideBox()->getY1() <= world->getIthTile(i)->getCollideBox().getY1()))
	    {//if touching tile from above
		e->y = world->getIthTile(i)->getCollideBox().getY1() - e->height;
		returnVal = true;
	    }
	    if((e->getCollideBox()->getY1() <= world->getIthTile(i)->getCollideBox().getY2() && e->getCollideBox()->getY2() >= world->getIthTile(i)->getCollideBox().getY2()))
	    {//if touching tile from below
		e->y = world->getIthTile(i)->getCollideBox().getY2() + 1;
		e->setYVelocity(0);
	    }
	}
    }
    e->setYCollided(returnVal);
}

