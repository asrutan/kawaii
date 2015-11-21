// game.cpp
// Alex Rutan
// 4/1/15
#include <iostream>
#include <SDL2/SDL.h>
#include <cmath>
#include "game.h"
#include "hud.h"

using namespace std;

/*
Game constructor 
defines the values used for the resolution of the screen
initializes values used by SDL for renderer, window, and textures
 */
Game::Game()
{
    resX = 800;
    resY = 600;
    window = NULL;
    surface = NULL;
    renderer = NULL;
} //end constructor

Game::~Game()
{
} //end destructor


/*
Initializes SDL and creates window, renderer, and assigns values for their initialization
Has checks to make sure everythin initializes properly
Otherwise it would be very hard to pinpoint what is breaking when nothing happens
 */
bool Game::init()
{
    bool success = true;
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
	printf("SDL broke or something.");
	success = false;
    } //end if
    else
    {
	window = SDL_CreateWindow("Shooter", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, resX, resY, SDL_WINDOW_SHOWN);
	if(window == NULL)
	{
	    printf("Window Can't Be Created Fool");
	    success = false;
	}
	else
	{
	    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	    if(!renderer)
	    {
		cout << "Couldn't create window :( " << endl;
		cout << SDL_GetError() << endl;
		success = false;
	    } //end if
	    else
	    {
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	    } //end else
	} //end else
    } //end else
    return success;
} //end init

/*
Destroy each of the textures, surface, window, and renderer
Otherwise things hang around in memory
Execute "SDL_Quit()" to properly close SDL
 */
void Game::close()
{
    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    SDL_FreeSurface(surface);
    surface = NULL;

    SDL_DestroyWindow(window);
    window = NULL;

    SDL_Quit();
} //end close

void Game::rotate(bool right)
{
    if(right)
    {
	playerDir = playerDir + 10;
	if(playerDir > 360)
	{
	    playerDir = 0;
	} //end if
    } //end if
    else
    {
	playerDir = playerDir - 10;
        if(playerDir < 0)
	{
	    playerDir = 360;
	} //end if
    } //end if
    dy = sin(M_PI/180 * playerDir);
    dx = cos(M_PI/180 * playerDir);

} // end rotate

/*
First, take each of the textures and assign them to their own specific rectangles to be drawn later
Create and instance of map, map is loaded when it is constructed
Pass the map information on to player and the setEnemyMap via pointer
Create an instance of camera and send it values for number of rays and player's initial position
Create an instance of SDL_Event for player input, events change bools to "true"
 */
int Game::run()
{
    SDL_Event event;
    
    bool forward = false;
    bool backward = false;
    bool sleft = false;
    bool sright = false;
    bool rrotate = false;
    bool lrotate = false;

    playerx = resX/2;
    playery = resY/2;
    playerDir = 0;

    wallx1 = 50;
    wally1 = 80;
    wallx2 = 90; 
    wally2 = 40;

    Hud hud;
    hud.init(&playerx);

    if (!init())
    {
	printf("Coudn't initialize");
    } //end if
    else
    {
        bool keepGoing = true;
        while(keepGoing)
        {
	    while(SDL_PollEvent(&event) != 0)
		{
		    if(event.type == SDL_KEYDOWN)
		    {	
			if(event.key.keysym.sym == SDLK_ESCAPE)
			{
			    keepGoing = false;
			} //end if
			if(event.key.keysym.sym == SDLK_w)
			{
			    forward = true;
		       	} //end if
			if(event.key.keysym.sym == SDLK_s)
			{
			    backward = true;
			} //end if
			if(event.key.keysym.sym == SDLK_a)
			{
			    sleft = true;
		       	} //end if
			if(event.key.keysym.sym == SDLK_d)
			{
			    sright = true;
			} //end if
			if(event.key.keysym.sym == SDLK_RIGHT)
			{
			    rrotate = true;
			} //end if
			if(event.key.keysym.sym == SDLK_LEFT)
			{
			    lrotate = true;
			} //end if
		    } //end if

		    if(event.type == SDL_KEYUP)
		    {	
			if(event.key.keysym.sym == SDLK_w)
			{
			    forward = false;
		       	} //end if
			if(event.key.keysym.sym == SDLK_s)
			{
			    backward = false;
			} //end if
			if(event.key.keysym.sym == SDLK_a)
			{
			    sleft = false;
		       	} //end if
			if(event.key.keysym.sym == SDLK_d)
			{
			    sright = false;
			} //end if
			if(event.key.keysym.sym == SDLK_RIGHT)
			{
			    rrotate = false;
			} //end if
			if(event.key.keysym.sym == SDLK_LEFT)
			{
			    lrotate = false;
			} //end if
		    } //end if
		} //end while
		
		/*
		  Update the surface on which everything is drawn every loop
		  Set the draw color to the color of the ceiling and then clear the screen, which turns the whole screen that color
		 */
		SDL_UpdateWindowSurface(window);	
		SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);		
		SDL_RenderClear(renderer);
		
		/*
		  Calls the functions in player that are associated with inputs
		 */
		/*		if(forward)
		{
		    //    forward = false;
		    p.move (1);
		} //end if
		if(backward)
		{
		    //    backward = false;
		    p.move (0);
		} //end if
		if(sleft)
		{
		    // sleft = false;
		    p.move (1);
		} //end if
		if(sright)
		{
		    // sright = false;
		    p.move (0);
		} //end if
		if(rrotate)
		{
		    p.rotate(5);
		} //end if
		if(lrotate)
		{
		    p.rotate(-5);
		    } //end if*/

		if(forward)
		{
		    playerx = playerx + 3*dx;
		    playery = playery + 3*dy;
		} //end if
		if(backward)
		{
		    playerx = playerx - 2*dx;
		    playery = playery - 2*dy;
		} //end if
		if(sleft)
		{
		    playerx--;
		} //end if
		if(sright)
		{
		    playerx++;
		} //end if
		if(rrotate)
		{
		    rotate(true);
		} //end if
		if(lrotate)
		{
		    rotate(false);
		} //end if

		//twx1 = (wallx1 - playerx * dx);
		//twy1 = (wally1 - playery * dy);
		//twx2 = (wallx2 - playerx * dx);
	       	//twy2 = (wally2 - playery * dy);

		twx1 = wallx1 - playerx; 
		twy1 = wally1 - playery;
		twx2 = wallx2 - playerx; 
		twy2 = wally2 - playery;

		//can probably replace the cos/sin functions with dx and dy as updated in rotate()
		twz1 = twx1 * cos(M_PI/180 * playerDir) + twy1 * sin(M_PI/180 * playerDir);
		twz2 = twx2 * cos(M_PI/180 * playerDir) + twy2 * sin(M_PI/180 * playerDir);
	        twx1 = twx1 * sin(M_PI/180 * playerDir) - twy1 * cos(M_PI/180 * playerDir);
	        twx2 = twx2 * sin(M_PI/180 * playerDir) - twy2 * cos(M_PI/180 * playerDir);

		//sin(M_PI/180 * playerDir)
		//cos(M_PI/180 * playerDir)

		//cout << playerDir << endl;
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderDrawLine(renderer, (resX/2) - twx1, (resY/2) - twz1, (resX/2) - twx2, (resY/2) - twz2);
		SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
		SDL_RenderDrawLine(renderer, resX/2, resY/2, resX/2, resY/2 - 10);
		//SDL_RenderDrawLine(renderer, playerx, playery, playerx + 1, playery + 1);
		
		//SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
		//SDL_RenderDrawLine(renderer, wallx1, wally1, wallx2, wally2);
		//SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
		//SDL_RenderDrawLine(renderer, resX/2, resY/2, resX/2, resY/2 - 10);
		//SDL_RenderDrawLine(renderer, playerx, playery, playerx + 1, playery + 1);
		
		//This updates the screen with what has been drawn on the renderer
		SDL_RenderPresent(renderer);

		hud.disp();
		
		//We have a blanket delay since the game is not intensive on any semi-modern system
		//One day we'll intelligently set the framerate
	       	SDL_Delay(40);

		// end updates
	    } //end while 
        } //end else    
    return (0);
}
 //end run
