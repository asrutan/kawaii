// player.cpp
// Alex Rutan
// 11//21/15
#include <iostream>
#include <cmath>
#include "player.h"
#include "movement.h"

using namespace std;

Player::Player()
{
    movement;
    x = 0;
    y = 0;
    quit = false;
} //end constructor

Player::~Player()
{
} //end deconstructor

void Player::update()
{
    movement.keyEvents();
    move();
} //end update

void Player::move()
{
    if(movement.right)
    {
        x++;
        cout << x << endl;
    } //end if
    if(movement.left)
    {
        x--;
        cout << x << endl;
    } //end if
    if(movement.jump)
    {
        y++;
        cout << y << endl;
    } //end if
    if(movement.quit)
    {
        quit = true;
    } //end if
} //end move
