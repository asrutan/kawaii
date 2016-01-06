// entity.cpp
// PA
// 1/5/16
#include <iostream>
#include <cmath>
#include "entity.h"
#include "collideBox.h"

using namespace std;

Entity::Entity()
{
    cBox = collideBox(x, x+50, y, y + 50);
    speed = 0;
    airbound = false;
    xCollided = false;
    yCollided = false;
    yVelocity = 0;
    xVelocity = 0;
    xNew = 0;
    //end private vars
    x = 0;
    y = 0;
    left = false;
    right = false;
    height = 50;
    width = 50;
    //end public vars
} //end constructor

Entity::~Entity()
{
} //end deconstructor

void Entity::update()
{
    xNew = x;
    tryMove();
    x = xNew;
    //cout << x << endl;
    //move();
} //end update

void Entity::tryMove()
{
    if(right)
    {
	if(xCollided)
	{
	    right = false;
	    left = true;
	}
	else
	{
	    xNew = x + 5;
	}
    }
    if(left)
    {
	if(xCollided)
	{
	    left = false;
	    right = true;
	}
	else
	{
	    xNew = x - 5;
	}
    }
    if(!yCollided)
    {
	airbound = true;
    } //end if
    cBox.update(xNew, xNew + width, y, y + height);
} //end move

void Entity::fall()
{
    if(y < 10000)//max y dist at 800
    { 
        y = y - yVelocity;
        yVelocity--;
	if(yVelocity <= -45)
	{
	    yVelocity = -45;
	}
	//cBox.update(x, x + width, y, y + height);
	checkBottom();
    }
    else
    {
	y = 799;
	yVelocity = 0;
	airbound = false;
	yCollided = true;
    }
} //end fall

collideBox* Entity::getCollideBox()
{
    return &cBox;
}//end getCollideBox

void Entity::checkBottom()
{
    if(yCollided)
    {
        //y = bottom - height;
	airbound = false;
	yVelocity = 0;
    } //end if
} //end checkBottom

void Entity::setXCollided(bool c)
{
    xCollided = c;
}
void Entity::setYCollided(bool c)
{
    yCollided = c;
}
/*void Entity::setGround(int g)
{
    ground = g;
}
*/
void Entity::setX(int xNew)
{
    x = xNew;
}
void Entity::setY(int yNew)
{
    y = yNew;
}
void Entity::setYVelocity(int v)
{
    yVelocity = v;
}
void Entity::setXVelocity(int v)
{
    xVelocity = v;
}
void Entity::move()
{
    if(!xCollided)
    {
        x = xNew + xVelocity;
    }
    if(airbound)
    {
	fall();
    } //end if

    cBox.update(x, x + width, y, y + height);
}

int Entity::getNewX()
{
    return xNew;
}
