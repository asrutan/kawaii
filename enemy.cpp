// enemy.cpp
// Alex Rutan
// 1//3/16
#include <iostream>
#include "enemy.h"
#include "entity.h"
#include "collideBox.h"

using namespace std;

Enemy::Enemy()
{
    cBox = collideBox(x+50, x+60, y, y + 125);
    speed = 10;
    airbound = false;
    xCollided = 0;
    yCollided = false;
    yVelocity = 0;
    xVelocity = 0;
    xNew = 0;
    //end protected inherited vars

    x = 0;
    y = 0;
    height = 125;
    width = 10;

    //end public inherited vars
    left = false;
    right = true;
    tick = 0;
    frame = 0;
    //end new vars
} //end constructor

Enemy::~Enemy()
{
} //end deconstructor

void Enemy::update()
{
    xNew = x;
    tryMove();
    tick++;
    //cout << frame << endl;

    if(tick > 4)
    {
	tick = 0;
	frame++;
	if(frame > 7)
	{
	    frame = 0;
	} //end if
    } //end if
} //end update

void Enemy::tryMove()
{
    if(right)
    {
	xNew = x + 5;
    }
    if(left)
    {
	xNew = x - 5;
    }
    if(!yCollided)
    {
	airbound = true;
    } //end if
    cBox.update(xNew+50, xNew+60, y, y + 125);
    
} //end move

void Enemy::fall()
{
    if(y < 10000)//max y dist at 800
    { 
        y = y - yVelocity;
        yVelocity--;
	if(yVelocity <= -45)
	{
	    yVelocity = -45;
	}
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

void Enemy::checkBottom()
{
    if(yCollided)
    {
        //y = bottom - height;
	airbound = false;
	yVelocity = 0;
    } //end if
} //end checkBottom

void Enemy::move()
{
    if(xCollided == 0)
    {
        x = xNew;
    }
    else
    {
	if(right)
	{
	    right = false;
	    left = true;
	}
	else
	{
	    right = true;
	    left = false;
	}
    }
    if(airbound)
    {
	fall();
    } //end if

    cBox.update(x+50, x+60, y, y + 125);
}

void Enemy::hit()
{
    cout << "Enemy OW!!" << endl;
}
