// player.cpp
// Alex Rutan
// 11//21/15
#include <iostream>
#include <cmath>
#include "player.h"
#include "movement.h"
#include "collideBox.h"

using namespace std;

Player::Player()
{
    movement;
    airbound = false;
    xCollided = false;
    yCollided = false;
    //jumpReady = true;
    jumpStrength = 20;
    x = 0;
    xNew = 0;
    y = 0;
    cBox = collideBox(x, x + 100, y, y + 125);
    yVelocity = 0;
    height = 125;
    speed = 5;
    tick = 0;
    frame = 0;
    quit = false;
} //end constructor

Player::~Player()
{
} //end deconstructor

void Player::update()
{
    xNew = x;
    movement.keyEvents();
    tryMove();
    tick++;
    //cout << frame << endl;
    if(tick > 5)
    {
	tick = 0;
	frame++;
	if(frame > 7)
	{
	    frame = 0;
	} //end if
    } //end if
    /*else{
	jumpReady = true;
    } //end if*/
    //cout << airbound << endl;
} //end update

void Player::tryMove()
{
    if(movement.right)
    {
        xNew = x+speed;
	//x = xNew;
    } //end if
    if(movement.left)
    {
        xNew = x-speed;
	//x = xNew;
        //cout << x << endl;
    } //end if
    if(movement.jump && !airbound)
    {
	airbound = true;
        yVelocity = jumpStrength;
        //cout << y << endl;
    } //end if
    if(movement.quit)
    {
        quit = true;
    } //end if

    if(!yCollided)
    {
	airbound = true;
    } //end if
    cBox.update(xNew, xNew + 100, y, y + 125);
} //end move

void Player::fall()
{
    if(y < 1200)//max y dist at 800
    { 
        y = y - yVelocity;
        yVelocity--;
	cBox.update(x, x + 100, y, y + 125);
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

collideBox Player::getCollideBox()
{
    return cBox;
}//end getCollideBox

void Player::checkBottom()
{
    if(yCollided)
    {
        //y = bottom - height;
	airbound = false;
	yVelocity = 0;
    } //end if
} //end checkBottom

void Player::setXCollided(bool c)
{
    xCollided = c;
}
void Player::setYCollided(bool c)
{
    yCollided = c;
}
void Player::setGround(int g)
{
    ground = g;
}
void Player::setYVelocity(int v)
{
    yVelocity = v;
}
void Player::move()
{
    if(!xCollided)
    {
        x = xNew;
    }
    if(airbound)
    {
	fall();
    } //end if

    cBox.update(x, x + 100, y, y + 125);
}

int Player::getNewX()
{
    return xNew;
}

