// game.cpp
// Alex Rutan
// 4/1/15
#include <iostream>
#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <cmath>
#include "game.h"
#include "hud.h"
#include "movement.h"
#include "player.h"

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
    playerTexture = NULL;
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
	window = SDL_CreateWindow("Kawaii", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, resX, resY, SDL_WINDOW_SHOWN);
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

bool Game::loadTextures()
{
    bool success = true;
    surface = SDL_LoadBMP("player.bmp");
    if(surface == NULL)
    {
	printf("Couldn't load textures sry :(");
	cout << SDL_GetError() << endl;
	success = false;
    } //end if
    else{
        playerTexture = SDL_CreateTextureFromSurface(renderer, surface);
	if(playerTexture == NULL)
	{
	    success = false;
	} //end if
    } //end else
    return success;
} //end loadTextures


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

    SDL_DestroyTexture(playerTexture);
    playerTexture = NULL;

    //IMG_Quit(); this library is not currently installed
    SDL_Quit();
} //end close


/*
First, take each of the textures and assign them to their own specific rectangles to be drawn later
Create and instance of map, map is loaded when it is constructed
Pass the map information on to player and the setEnemyMap via pointer
Create an instance of camera and send it values for number of rays and player's initial position
Create an instance of SDL_Event for player input, events change bools to "true"
 */
int Game::run()
{   
    Player player;
    Hud hud;
    //hud.init(&playerx);

    SDL_Rect srcPlayerRect;
    SDL_Rect dstPlayerRect;
    srcPlayerRect.x = 0;
    srcPlayerRect.y = 0;
    srcPlayerRect.w = 400;
    srcPlayerRect.h = 854;
    dstPlayerRect.x = player.x;
    dstPlayerRect.y = player.y;
    dstPlayerRect.w = 50;
    dstPlayerRect.h = 106;

    if (!init())
    {
	printf("Coudn't initialize");
    } //end if
    else if (!loadTextures())
    {
        printf("shit's fucked.");
    } //end if
    else
    {
        bool keepGoing = true;
        while(keepGoing)
        {
	    player.update();
	    if(player.quit)
	    {
		keepGoing = false;
	    } //end if
  
	    dstPlayerRect.x = player.x;
	    dstPlayerRect.y = player.y;

	    SDL_UpdateWindowSurface(window);	
	    SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
	    SDL_RenderClear(renderer);		 

            SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
            SDL_RenderDrawLine(renderer, 0, 500, resX, 500);

	    SDL_RenderCopy(renderer, playerTexture, &srcPlayerRect, &dstPlayerRect);

	    

	    //This updates the screen with what has been drawn on the renderer
	    SDL_RenderPresent(renderer);
	    
	    //hud.disp();
	    //We have a blanket delay since the game is not intensive on any semi-modern system
	    //One day we'll intelligently set the framerate
	    SDL_Delay(40);

	    // end updates
	} //end while 
    } //end else    
    return (0);
}
 //end run
