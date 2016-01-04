// enemy.cpp
// Alex Rutan
// 1//3/16
#include <iostream>
#include <cmath>
#include "enemy.h"
#include "collideBox.h"

using namespace std;

Enemy::Enemy()
{
    airbound = false;
    xCollided = false;
    yCollided = false;
    //jumpReady = true;
    x = 0;
    xNew = 0;
    y = 0;
    cBox = collideBox(x+50, x+60, y, y + 125);
    yVelocity = 0;
    height = 125;
    speed = 10;
    tick = 0;
    frame = 0;
    //make this an array or list or some shit
    //
} //end constructor

Enemy::~Enemy()
{
} //end deconstructor

void Enemy::update()
{
    xNew = x;
    xNew = x+xVelocity;
    tryMove();
    move();
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
	cBox.update(x+50, x+60, y, y + 125);
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

collideBox Enemy::getCollideBox()
{
    return cBox;
}//end getCollideBox

void Enemy::checkBottom()
{
    if(yCollided)
    {
        //y = bottom - height;
	airbound = false;
	yVelocity = 0;
    } //end if
} //end checkBottom

void Enemy::setXCollided(bool c)
{
    xCollided = c;
}
void Enemy::setYCollided(bool c)
{
    yCollided = c;
}
void Enemy::setGround(int g)
{
    ground = g;
}
void Enemy::setYVelocity(int v)
{
    yVelocity = v;
}
void Enemy::move()
{
    if(!xCollided)
    {
        x = xNew;
    }
    if(airbound)
    {
	fall();
    } //end if

    cBox.update(x+50, x+60, y, y + 125);
}

int Enemy::getNewX()
{
    return xNew;
}

/*void Player::attack()
{
    
} //end attack


//if x + 1 collides, x velocity = 0
//consider the preceding for collision detection*/
