//display.cpp
//Alex Rutan / PA
//11/22/15

#include <iostream>
#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <string.h>
#include <cmath>
#include "display.h"

using namespace std;

Display::Display()
{
    resX = 800;
    resY = 600;
    window = NULL;
    surface = NULL;
    renderer = NULL;
}//end constructor

Display::~Display()
{
}//end deconstructor


/*
Initializes SDL and creates window, renderer, and assigns values for their initialization
Has checks to make sure everythin initializes properly
wiOtherwise it would be very hard to pinpoint what is breaking when nothing happens
*/

bool Display::init()
{
    bool success = true;
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
	printf("SDL broke or something.");
	success = false;
    } //end if
    else
    {
	window = SDL_CreateWindow("Kawaii", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, resX, resY, SDL_WINDOW_SHOWN);
	if(window == NULL)
	{
	    printf("Window Can't Be Created Fool");
	    success = false;
	}
	else
	{
	  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); //present vsync caps framerate at monitor refresh rate, in most cases 60hz so 60 fps
	    if(!renderer)
	    {
		cout << "Couldn't create window :( " << endl;
		cout << SDL_GetError() << endl;
		success = false;
	    } //end if
	    else
	    {
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		int imgFlags = IMG_INIT_PNG;
	    	if(!(IMG_Init(imgFlags) & imgFlags))
	       	{
	       	    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
	            success = false;
		}

	        //Initialize SDL_ttf
	     	if(TTF_Init() == -1)
		{
		    printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
       	    	    success = false;
		}
	    } //end else
	} //end else
    } //end else
    return success;
}//end init

void Display::close()
{
    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    SDL_FreeSurface(surface);
    surface = NULL;

    SDL_DestroyWindow(window);
    window = NULL;

    //IMG_Quit(); this library is not currently installed
    SDL_Quit();
    TTF_Quit();
    IMG_Quit();
}

SDL_Renderer* Display::getRenderer()
{
    return renderer;
}

SDL_Window* Display::getWindow()
{
    return window;
}

bool Display::loadTextures()
{
    bool success = true;
    //TODO implement texture load functions
    /*surface = SDL_LoadBMP("player.bmp");
    if(surface == NULL)
    {
	printf("Couldn't load textures sry :(");
	cout << SDL_GetError() << endl;
	success = false;
    } //end if
    else
    {
        playerTexture = SDL_CreateTextureFromSurface(renderer, surface);
	if(playerTexture == NULL)
	{
	    success = false;
	} //end if
    } //end else*/
    return success;
} //end loadTextures

int Display::getResX()
{
    return resX;
}//end getResX

int Display::getResY()
{
    return resY;
}
