// game.cpp
// Alex Rutan
// 4/1/15
#include <iostream>
#include <sstream>
#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <string.h>
#include <cmath>
#include "game.h"
#include "hud.h"
#include "movement.h"
#include "player.h"
#include "display.h"
#include "texture.h"
#include "textTexture.h"
#include "tile.h"

using namespace std;

/*
Game constructor 
defines the values used for the resolution of the screen
initializes values used by SDL for renderer, window, and textures
 */
Game::Game()
{
    player = Texture(&display);
    font = textTexture(&display);
    tiles = new Tile[12];
    for(int i = 0; i < 12; i++)
    {
        //cout << i << endl;
        tiles[i] = Tile(&display);
    }
} //end constructor

Game::~Game()
{
} //end destructor

bool Game::loadTextures()
{
    bool success = true;
    if(!player.makeTexture("player.bmp"))
    {
        cout << "Player texture failed" << endl;
	success = false;
    }
    if(!font.loadFontMedia("/usr/share/fonts/truetype/fonts-japanese-gothic.ttf"))
    {
        cout << "Font texture failed" << endl;
	success = false;
    }
    for(int i = 0; i < 12; i++)
    {
        if(!tiles[i].textureTile("blocks.png"))
        {
  	    cout << "tile texture failed" << endl;
	    success = false;
        }
    }
    
    return success;
} //end loadTextures


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

    SDL_Rect srcTileRects[12];
    SDL_Rect dstTileRects[12];
    int tileSize = 50;

    for(int j = 0; j < 12; j++)
    {
	srcTileRects[j].x = 0;
	srcTileRects[j].y = 0;
	srcTileRects[j].w = tileSize;
	srcTileRects[j].h = tileSize;

	dstTileRects[j].x = 0;
	dstTileRects[j].y = tileSize*j;
	dstTileRects[j].w = tileSize;
	dstTileRects[j].h = tileSize;
    }

    if (!display.init())
    {
	printf("Coudn't initialize");
    } //end if
    else if (!loadTextures())
    {
        printf("Failed to load Texture(s)");
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
  
	    dstPlayerRect.x = display.getResX()/2-50/2;
	    dstPlayerRect.y = display.getResY()/2-106/2;

	    SDL_UpdateWindowSurface(display.getWindow());	
	    SDL_SetRenderDrawColor(display.getRenderer(), 80, 80, 80, 255);
	    SDL_RenderClear(display.getRenderer());		 

            SDL_SetRenderDrawColor(display.getRenderer(), 200, 200, 200, 255);
            //SDL_RenderDrawLine(display.getRenderer(), 0, 500, display.getResX(), 500);

	    SDL_RenderDrawLine(display.getRenderer(), 0-player.x+display.getResX()/2-50/2, 500-player.y+display.getResY()/2-106/2, 300-player.x+display.getResX()/2-50/2, 500-player.y+display.getResY()/2-106/2);
            SDL_RenderDrawLine(display.getRenderer(), 300-player.x+display.getResX()/2-50/2, 200-player.y+display.getResY()/2-106/2, display.getResX()-player.x+display.getResX()/2-50/2, 200-player.y+display.getResY()/2-106/2);

	    SDL_RenderCopy(display.getRenderer(), this->player.getTexture(), &srcPlayerRect, &dstPlayerRect);


            SDL_SetRenderDrawColor(display.getRenderer(), 255,255,255,255);
            //SDL_RenderCopy(renderer, textTexture, NULL, NULL);

	    stringstream strs;
	    strs << player.x / 20 << " Meters";
	    string str = strs.str();

	    font.loadFontFromRenderedText(str, {50, 50, 225});

	    font.renderTextTexture((display.getResX() - font.getFontFileWidth()) / 2, 550);

	    for(int k = 0; k < 12; k++)
	    {
	      SDL_RenderCopy(display.getRenderer(), tiles[k].getTexture(), &srcTileRects[k], &dstTileRects[k]);
	    }

	    //This updates the screen with what has been drawn on the renderer
	    SDL_RenderPresent(display.getRenderer());
	    
	    //hud.disp();
	    //We have a blanket delay since the game is not intensive on any semi-modern system
	    //One day we'll intelligently set the framerate
	    SDL_Delay(40);

	    // end updates
	} //end while 
    } //end else 
    display.close();
    return (0);
}//end run
