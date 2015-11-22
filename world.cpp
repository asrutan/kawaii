// world.cpp
// Alex Rutan
// 11/22/15
#include <iostream>
#include "world.h"

using namespace std;

World::World()
{
    ground = 500;
} //end constructor

World::~World()
{
} //end destructor

int World::getGround()
{
    return(ground);
} //end getGround
