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
    cBox = collideBox(x+50, x+60, y, y + 125);
    yVelocity = 0;
    xVelocity = 0;
    height = 125;
    speed = 10;
    tick = 0;
    frame = 0;
    //make this an array or list or some shit
    animForward = false;
    animBackward = false;
    animIdle = true;
    //
    quit = false;
} //end constructor

Player::~Player()
{
} //end deconstructor

void Player::update()
{
    xNew = x;
    movement.keyEvents();
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
    /*else{
	jumpReady = true;
    } //end if*/
    //cout << airbound << endl;
} //end update

void Player::tryMove()
{
    if(movement.right)
    {
	animForward = true;
	animIdle = false;
	if(xVelocity+1 <= speed)
	{ 
	    xVelocity++;
	} //end if
        //xNew = x+xVelocity;
	//x = xNew;
    } //end if
    else if(!movement.right)
    {
	animForward = false;
	animIdle = true;
	if(xVelocity > 0)
	{ 
	    xVelocity--;
	} //end if
    } //end elif
    
    if(movement.left)
    {
	animBackward = true;
	animIdle = false;
	if(xVelocity-1 >= speed*-1)
	{ 
	    xVelocity--;
	} //end if
        //xNew = x+xVelocity;
	//x = xNew;
        //cout << x << endl;
    } //end if
    else if(!movement.left)
    { 
	animBackward = false;
	if(xVelocity < 0)
	{ 
	    xVelocity++;
	} //end if
    } //end elif
	    
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
    cBox.update(xNew+50, xNew+60, y, y + 125);
} //end move

void Player::fall()
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

    cBox.update(x+50, x+60, y, y + 125);
}

int Player::getNewX()
{
    return xNew;
}

/*void Player::attack()
{
    
} //end attack


//if x + 1 collides, x velocity = 0
//consider the preceding for collision detection */
