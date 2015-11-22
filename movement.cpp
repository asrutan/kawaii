// movement.cpp
// Alex Rutan
// 11/21/15
#include <iostream>
#include <SDL2/SDL.h>
#include <cmath>
#include "movement.h"

using namespace std;

Movement::Movement()
{
    SDL_Event event;
    quit = false;
    left = false;
    right = false;
    jump = false;
} //end constructor

Movement::~Movement()
{
    quit = false;
    left = false;
    right = false;
    jump = false;
} //end destructor

void Movement::keyEvents()
{
    while(SDL_PollEvent(&event) != 0)
    {
        if(event.type == SDL_KEYDOWN)
        {	
            if(event.key.keysym.sym == SDLK_ESCAPE)
            {
                setTrue(&quit);
            } //end if
            if(event.key.keysym.sym == SDLK_RIGHT)
            {
                setTrue(&right);
            } //end if
            if(event.key.keysym.sym == SDLK_LEFT)
	    {
                setTrue(&left);
            } //end if
            if(event.key.keysym.sym == SDLK_SPACE)
            {
                setTrue(&jump);
            } //end if
        } //end if
    
        if(event.type == SDL_KEYUP)
        {	
            if(event.key.keysym.sym == SDLK_RIGHT)
            {
                setFalse(&right);
            } //end if
            if(event.key.keysym.sym == SDLK_LEFT)
            {
                setFalse(&left);
            } //end if
            if(event.key.keysym.sym == SDLK_SPACE)
            {
                setFalse(&jump);
            } //end if
        } //end if
    } //end while
} //end keyEvents

void Movement::setTrue(bool *action)
{
    *action = true;
} //end setTrue

void Movement::setFalse(bool *action)
{
    *action = false;
} //end setFalse
