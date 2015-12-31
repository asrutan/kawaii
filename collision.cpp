// collision.cpp
// PA
// 12/01/15

#include <iostream>
#include "player.h"
#include "world.h"
#include "collision.h"
#include "collideBox.h"

using namespace std;

Collision::Collision()
{
    *player = Player();
    *world = World();
}

Collision::Collision(Player* p, World* w)
{
    player = p;
    world = w;
}

Collision::~Collision()
{

}

void Collision::playerWallCollision(collideBox pcBox)
{
    bool returnVal = false;
    for(int i = 0; i < world->getTileCount(); i++)
    {
	//if(!returnVal)//makes sure only topmost tile is checked
	//{
	if(pcBox.getX1() <= world->getIthTile(i)->getCollideBox().getX2() && pcBox.getX2() >= world->getIthTile(i)->getCollideBox().getX1())//Collide from left
	{//if outside of given x tile
	    if(pcBox.getY1() >= world->getIthTile(i)->getCollideBox().getY1() && pcBox.getY1() <= world->getIthTile(i)->getCollideBox().getY2())
	    {//if inside of given y tile
		returnVal = true;
		//cout << "X Collide" << endl;
	    }
	    if(world->getIthTile(i)->getCollideBox().getY1() >= pcBox.getY1() && world->getIthTile(i)->getCollideBox().getY2() <= pcBox.getY2())
	    {
		returnVal = true;
	    }
	    if(pcBox.getY2() > world->getIthTile(i)->getCollideBox().getY1() && pcBox.getY2() < world->getIthTile(i)->getCollideBox().getY2())
	    {
		returnVal = true;
	    }
	}
	//}
      //returnVal = true;
      //if(y >= world->getIthTile(i)->getYPos() - 25 && y <= world->getIthTile(i)->getYPos() +25)
      //    returnVal = true;
    }//end for
    player->setXCollided(returnVal);
}

void Collision::checkFloorCollision(collideBox pcBox)
{
    bool returnVal = false;
    //int returnVal = 800;
    for(int i = 0; i < world->getTileCount(); i++)
    {
        if(pcBox.getX1() < world->getIthTile(i)->getCollideBox().getX2() && pcBox.getX2() > world->getIthTile(i)->getCollideBox().getX1())
        {//if inside of given x tile
	    //cout << "in outter if" << endl;
	    if((pcBox.getY2() >= world->getIthTile(i)->getCollideBox().getY1() && pcBox.getY1() <= world->getIthTile(i)->getCollideBox().getY1()))//|| y >= world->getIthTile(i)->getYPos() + 25)
	    {//if touching tile from above
		//returnVal = world->getIthTile(i)->getYPos();
		player->y = world->getIthTile(i)->getCollideBox().getY1() - player->height;
		returnVal = true;
		//cout << "Touching tile from Above" << endl;
	    }
	    if((pcBox.getY1() <= world->getIthTile(i)->getCollideBox().getY2() && pcBox.getY2() >= world->getIthTile(i)->getCollideBox().getY2()))
	    {//if touching tile from below
		player->y = world->getIthTile(i)->getCollideBox().getY2() + 1;
		player->setYVelocity(0);
		//cout << "Touching tile from below" << endl;
		//returnVal = true;
	    }
	}
	//player->setGround(returnVal);
    }
    player->setYCollided(returnVal);
}


