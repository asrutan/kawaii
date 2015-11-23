// world.cpp
// Alex Rutan
// 11/22/15
#include <iostream>
#include "world.h"

using namespace std;

World::World()
{
    ground1 = 500;
    ground2 = 200;
    ground3 = 800;
    wall1x = 300;
    wall1y1 = 200;
    wall1y2 = 500;
} //end constructor

World::~World()
{
} //end destructor

int World::getGround(int playerX)
{
    return(regionRange(playerX));
} //end getGround

int World::regionRange(int playerX)
{
    if(playerX < 300)
    {
	return(ground1);
    } //end if
    else if(playerX > 300)
    {
	return(ground2);
    } //end else if
} //end regionRange
