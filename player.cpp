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
    jumpStrength = 15;
    x = 0;
    xNew = 0;
    y = 20;
    yVelocity = 0;
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
    
    // cout << x << endl;
    // cout << y << endl;

    /*else{
	jumpReady = true;
    } //end if*/
    //cout << airbound << endl;
} //end update

void Player::move()
{
    if(movement.right)
    {
        xNew = x+speed;
	//if(checkCollide(xNew, y))
	//{
	//    xNew = x;
	//} //end if
	x = xNew;
    } //end if
    if(movement.left)
    {
        xNew = x-speed;
	//if(checkCollide(xNew, y))
	//{
	//    xNew = x;
	//} //end if
	x = xNew;

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

    if(y != world.getGround(x))
    {
	airbound = true;
    } //end if
} //end move

void Player::fall()
{
    y = y - yVelocity;
    yVelocity--;
    checkBottom(world.getGround(x));
    //checkBottom(500);
} //end fall

void Player::checkBottom(int bottom)
//void Player::checkBottom()
{
    if(bottom <= y+height)
    {
	y = bottom - height;
	airbound = false;
    } //end if
} //end checkBottom

/*
bool Player::checkCollide(int checkX, int checkY)
{
    if(world.checkWall(checkX, checkY))
    {
	return(true);
    } //end if
    else{
	return(false);
    } //end else
} //end checkCollide
*/
