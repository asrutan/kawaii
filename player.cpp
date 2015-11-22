// player.cpp
// Alex Rutan
// 11//21/15
#include <iostream>
#include <cmath>
#include "player.h"
#include "movement.h"
#include "world.h"

using namespace std;

Player::Player()
{
    world;
    movement;
    airbound = false;
    //jumpReady = true;
    x = 0;
    y = 0;
    height = 106;
    speed = 5;
    quit = false;
} //end constructor

Player::~Player()
{
} //end deconstructor

void Player::update()
{
    movement.keyEvents();
    move();
    if(airbound)
    {
	fall();
    } //end if
    
    /*else{
	jumpReady = true;
    } //end if*/
    //cout << airbound << endl;
} //end update

void Player::move()
{
    if(movement.right)
    {
        x = x+speed;
        //cout << x << endl;
    } //end if
    if(movement.left)
    {
        x = x-speed;
        //cout << x << endl;
    } //end if
    if(movement.jump && !airbound)
    {
	airbound = true;
        yVelocity = 20;
        //cout << y << endl;
    } //end if
    if(movement.quit)
    {
        quit = true;
    } //end if
} //end move

void Player::fall()
{
    y = y - yVelocity;
    yVelocity--;
    checkBottom(world.getGround());
} //end fall

void Player::checkBottom(int bottom)
{
    if(bottom <= y+height)
    {
	y = bottom - height;
	airbound = false;
    } //end if
} //end checkBottom
