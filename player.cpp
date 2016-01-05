// player.cpp
// Alex Rutan
// 11//21/15
#include <iostream>
#include <cmath>
#include "player.h"
#include "entity.h"
#include "movement.h"
#include "collideBox.h"

using namespace std;

Player::Player()
{
    cBox = collideBox(x+50, x+60, y, y + 125);
    speed = 10;
    airbound = false;
    xCollided = false;
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

    movement;
    tick = 0;
    frame = 0;
    //make this an array or list or some shit
    animForward = false;
    animBackward = false;
    animIdle = true;
    quit = false;
    jumpStrength = 20;
    //end new vars
} //end constructor

Player::~Player()
{
} //end deconstructor

void Player::update()//changed from entity
{
    xNew = x;
    movement.keyEvents();
    tryMove();
    //move();
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

void Player::tryMove()//changed from entity
{
    if(movement.right)
    {
	animForward = true;
	animIdle = false;
	if(xVelocity+1 <= speed)
	{ 
	    xVelocity++;
	} //end if
 
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

    } //end if
    else if(!movement.left)
    { 
	animBackward = false;
	//animIdle = true;
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
	//fall();
      	airbound = true;
    } //end if
    
    cBox.update(xNew + xVelocity + 50, xNew + xVelocity + 60, y, y + 125);
} //end move

void Player::fall()
{
    if(y < 10000)//max y dist at 800
    { 
        y = y - yVelocity;
        yVelocity--;
	if(yVelocity <= -45)
	{
	    yVelocity = -45;
	}
	//cBox.update(x+50, x+60, y, y + 125);
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

 void Player::checkBottom()
{
    if(yCollided)
    {
        //y = bottom - height;
	airbound = false;
	yVelocity = 0;
    } //end if
} //end checkBottom

void Player::move()
{
    if(!xCollided)
    {
        x = xNew + xVelocity;
    }
    //checkBottom();
    if(airbound)
    {
	fall();
	//checkBottom();
    } //end if
    
    cBox.update(x+50, x+60, y, y + 125);
}
