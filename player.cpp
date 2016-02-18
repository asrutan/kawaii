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
    spriteX = 50;//wraps collision box closer to sprite
    spriteY = 0;
    speed = 10;//movement speed
    airbound = false;//in air/ready to be in air
    xCollided = false;//is entity colliding in x direction
    yCollided = false;//is entity colliding in y direction
    yVelocity = 0;
    xVelocity = 0;
    xNew = 0;
    //end protected inherited vars

    x = 0;
    y = 0;
    height = 125;//height of player/sprite - used by collidebox
    width = 10;//width of player/sprite - used by collidebox
    //end public inherited vars

    movement;//listens to keystrokes
    tick = 0;//for animation
    frame = 0;
    //make this an array or list or some shit
    animForward = false;
    animBackward = false;
    animIdle = true;
    quit = false;
    jumpStrength = 20;//initial jump in pixels
    aBox = collideBox(x+60, x+160, y + 25, y + 100);//2 tile attack range
    attack = false;//are you attacking?
    attackCountUp = 0;
    attackCountDown = 0;
    lastMove = 'r';
    //end new vars
} //end constructor

Player::~Player()
{
} //end deconstructor

void Player::update()//changed from entity
{
    xNew = x;//store old x
    movement.keyEvents();//get movements
    attackCountDown--;//cooldown attack
    tryMove();//attempt to move.
    //move();
    tick++;
    //cout << frame << endl;

    if(tick > 4)//animation stuff
    {
	tick = 0;
	frame++;
	if(frame > 7)
	{
	    frame = 0;
	} //end if
    } //end if
} //end update

void Player::tryMove()//assesses keystrokes and passes values to collision
{
    if(movement.right)
    {
	lastMove = 'r';//for animation
	animForward = true;
	animIdle = false;
	if(xVelocity+1 <= speed)//increase velocity until at top speed
	{ 
	    xVelocity++;
	} //end if
 
    } //end if
    else if(!movement.right)
    {
	animForward = false;
	animIdle = true;
	if(xVelocity > 0)//slight coast at end of run
	{ 
	    xVelocity--;
	} //end if
    } //end elif
    
    if(movement.left)
    {
	lastMove = 'l';
	animBackward = true;
	animIdle = false;
	if(xVelocity-1 >= speed*-1)
	{ 
	    xVelocity--;
	} //end if

    } //end if
    else if(!movement.left)
    { 
	//lastMove = 'i';
	animBackward = false;
	//animIdle = true;
	if(xVelocity < 0)
	{ 
	    xVelocity++;
	} //end if
    } //end elif

    if(movement.attack)//attack check
    {
	if(attackCountDown <= 0)//if attack is ready
	{
	    attack = true;//set attacking to true
	    attackCountDown = 18;//set cooldown again
	}
	else//if attack not ready
	    attack = false;//don't attack
    }
	    
    if(movement.jump && !airbound)//if want to jump and not already in air
    {
	airbound = true;//prep to jump
        yVelocity = jumpStrength;
    } //end if
    if(movement.quit)//quits game -- MOVE TO MENU
    {
        quit = true;
    } //end if

    if(!yCollided)//if walked off edge or simmilar situation
    {
	//fall();
      	airbound = true;//prep to fall
    } //end if
    
    cBox.update(xNew + xVelocity + spriteX, xNew + xVelocity + (spriteX + width), y + spriteY, y + (spriteY + height));//update collide box for collision

    if(xCollided == 2)//TEMP fix for falling off vines when not holding direction.
    {
	//updates xNew anyway despite being xCollided
	if(lastMove == 'r')
	{
	    cBox.update(xNew + speed + spriteX, xNew + speed + (spriteX + width), y + spriteY, y + (spriteY + height));
	}
	else if(lastMove == 'l')
	{
	    cBox.update(xNew - speed + spriteX, xNew - speed + (spriteX + width), y + spriteY, y + (spriteY + height));
	}
    }
} //end move

void Player::fall()
{
    if(y < 10000)//max y dist at 10000
    { 
        y = y - yVelocity;//upadte y position
        yVelocity--;//decrement velocity. Allows deceleration when yV is neg && acceleration when yV is pos
	if(yVelocity <= -45)//terminal velocity.
	{
	    yVelocity = -45;//too high??
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

int Player::getXCollided()
{
    return xCollided;
}

 void Player::checkBottom()
{
    if(yCollided)//if y collided
    {
	airbound = false;//no longer in air
	yVelocity = 0;
    } //end if
} //end checkBottom

void Player::move()
{
    if(xCollided == 0)//if not xCollided
    {
	//CHECK THIS!! DONT NEED XNEW HERE??
        x = xNew + xVelocity;//update x by xVelocity
    }
    if(xCollided == 2)//if on climbing wall
    {
	airbound = false;//not in air
	yCollided = true;//act as if standing on ground
	yVelocity = 0;//stop upward or downward movement
    }
    if(airbound)//if in air
    {
	fall();
    } //end if
    
    cBox.update(x + spriteX, x + (spriteX + width), y + spriteY, y + (spriteY + height));//update collide box to actual values
    if(lastMove == 'r')//if last moving right
    {
	aBox.update(cBox.getX2(), cBox.getX2() + 100, cBox.getY1() + 25, cBox.getY2() - 25);//MAYBE GET CONSTS FROM WEAPON CLASS?
    }
    else if(lastMove == 'l')//if last moving left
    {
	aBox.update(cBox.getX1() - 100, cBox.getX1(), cBox.getY1() + 25, cBox.getY2() - 25);
    }
}

bool Player::attackCheck()//is player attacking
{
    return attack;
}

void Player::attackAction(Entity* e)//actual attack
{
    if(aBox.contains(*(e->getCollideBox())))//if attack range contains an entity
    {
	e->hit();//activate entity's hit method
    }
    attack = false;//set attack to false, even if nothing hit
}

void Player::hit()//when player hit
{
    cout << "Player OW!!" << endl;
}
