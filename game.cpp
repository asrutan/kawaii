// game.cpp
// Alex Rutan
// 4/1/15
#include <iostream>
#include <sstream>
#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <string>
#include <cmath>
#include "game.h"
#include "hud.h"
#include "movement.h"
#include "player.h"
#include "display.h"
#include "texture.h"
#include "textTexture.h"
#include "tile.h"
#include "world.h"
#include "camFocus.h"

using namespace std;

/*
Game constructor 
defines the values used for the resolution of the screen
initializes values used by SDL for renderer, window, and textures
 */
Game::Game()
{
    //cout << "game Started" << endl;
    playerTexture = Texture(&display);
    font = textTexture(&display);
    world = World(&display, "map.kwi");
    player = Player();
    //cout << "Game constructed" << endl;

} //end constructor

Game::~Game()
{
} //end destructor

bool Game::loadTextures()
{
    bool success = true;
    if(!playerTexture.makeTexture("player.gif"))
    {
        cout << "Player texture failed" << endl;
	success = false;
    }

    
    
    if(!font.loadFontMedia("/usr/share/fonts/truetype/fonts-japanese-gothic.ttf"))
    {
        cout << "Font texture failed" << endl;
	success = false;
    }
    for(int i = 0; i < world.getTileCount(); i++)
    {
        if(!world.getIthTile(i)->textureTile("blocks.png"))
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
    Collision collision = Collision(&player, &world);
    Hud hud;
    camFocus cam;
    //hud.init(&playerx);

    player.x = 100;
    player.y = 1000;
    //player.x = display.getResX()/2-50/2;
    //player.y = display.getResY()/2-106/2;

    //find a way to get this shit in player or something
    SDL_Rect srcPlayerRect;
    SDL_Rect dstPlayerRect;
    srcPlayerRect.x = 0;
    srcPlayerRect.y = 0;
    srcPlayerRect.w = 100;
    srcPlayerRect.h = 136;
    dstPlayerRect.x = player.x;
    dstPlayerRect.y = player.y;
    dstPlayerRect.w = 100;
    dstPlayerRect.h = 136;

    SDL_Rect srcTileRects[world.getTileCount()];
    SDL_Rect dstTileRects[world.getTileCount()];
    int tileSize = 50;

    //This doesn't go here
    for(int j = 0; j < world.getTileCount(); j++)
    {
        srcTileRects[j].x = 0;
	srcTileRects[j].y = 0;
	srcTileRects[j].w = tileSize;
	srcTileRects[j].h = tileSize;

	dstTileRects[j].x = world.getIthTile(j)->getXPos();
	dstTileRects[j].y = world.getIthTile(j)->getYPos();
	//cout << player.getWorld()->getIthTile(j).getYPos() << endl;
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
      bool campan = true;
      cam.x = 0;
      cam.y = 500;
        bool keepGoing = true;
        while(keepGoing)
        {
    	    player.update();
	    if(player.frame < 1)
	    {
		srcPlayerRect.x = 0;
	    } //end if
	    if(player.frame == 1)
	    {
		srcPlayerRect.x = 100;
	    } //end if
	    if(player.frame == 2)
	    {
		srcPlayerRect.x = 200;
	    } //end if
	    if(player.frame == 3)
	    {
		srcPlayerRect.x = 300;
	    } //end if
	    if(player.frame == 4)
	    {
		srcPlayerRect.x = 400;
	    } //end if
	    if(player.frame == 5)
	    {
		srcPlayerRect.x = 500;
	    } //end if
	    if(player.frame == 6)
	    {
		srcPlayerRect.x = 600;
	    } //end if
	    if(player.frame == 7)
	    {
		srcPlayerRect.x = 700;
	    } //end if
	    collision.playerWallCollision(player.getCollideBox());
	    collision.checkFloorCollision(player.getCollideBox());
	    player.move();
	    if(player.quit)
	    {
		keepGoing = false;
	    } //end if
	    
	    //cout << player.y << endl;
	    
	    cam.x = player.x-400;
	    cam.y = player.y-300;

	    //cam.x = cam.x - 400;
	    //cam.y = cam.y - 300;
	    
	    if(cam.x == -50)
	      {
	        campan = false;
	      }
	    if(cam.x == 50)
	      {
	        campan = true;
		} //end else */
	    
	    if(campan)
	      {
		cam.x--;
		cam.y--;
	      }
	    if(campan)
	      {
		cam.x++;
		cam.y++;
	      }

	    for(int i = 0; i < world.getTileCount(); i++)
	    {
	        //MOVE TO GLOBAL UPDATE CLASS?
	        //Change destination to draw to based on player movement:
	        dstTileRects[i].x = world.getIthTile(i)->getXPos() - cam.x;
		//cout << world.getIthTile(i)->getXPos() << endl;
	        dstTileRects[i].y = world.getIthTile(i)->getYPos() - cam.y;
	        //cout << tiles[i].getXPos() << endl;
	    }
	    
	    //center camera
	    //cam.x = cam.x - 400;
	    //cam.y = cam.y - 300;
	    
	    //cout << player.x << endl;
	    //cout << player.y << endl;

	    dstPlayerRect.x = player.x - cam.x;
	    dstPlayerRect.y = player.y - cam.y;

	    //player.x = world.getIthTile(8)->getXPos() + 10;
	    //player.y = world.getIthTile(8)->getYPos() + 10;

	    SDL_UpdateWindowSurface(display.getWindow());	
	    SDL_SetRenderDrawColor(display.getRenderer(), 80, 80, 80, 255);
	    SDL_RenderClear(display.getRenderer());		 

            SDL_SetRenderDrawColor(display.getRenderer(), 200, 200, 200, 255);
            //SDL_RenderDrawLine(display.getRenderer(), 0, 500, display.getResX(), 500);
	    
	    /*
	    SDL_RenderDrawLine(display.getRenderer(), 0-cam.x, 500-cam.y, 300-cam.x, 500-cam.y);// draw line centered on player in x direction and below player in Y direction
	    //x1 = 0(Origin) - player pos + center of screen - player size offset
            SDL_RenderDrawLine(display.getRenderer(), 300-cam.x, 200-cam.y, display.getResX()-cam.x+display.getResX()/2-50/2, 200-cam.y+display.getResY()/2-106/2);
	    */
	    SDL_RenderCopy(display.getRenderer(), playerTexture.getTexture(), &srcPlayerRect, &dstPlayerRect);


            SDL_SetRenderDrawColor(display.getRenderer(), 255,255,255,255);
            //SDL_RenderCopy(renderer, textTexture, NULL, NULL);

	    stringstream strs;
	    strs << "X: " << player.x << "  Y: " << player.y << "Pixels";
	    string str = strs.str();

	    font.loadFontFromRenderedText(str, {50, 50, 225});

	    font.renderTextTexture((display.getResX() - font.getFontFileWidth()) / 2, 550);

	    for(int k = 0; k < world.getTileCount(); k++)
	    {
	      SDL_RenderCopy(display.getRenderer(), world.getIthTile(k)->getTexture(), &srcTileRects[k], &dstTileRects[k]);
	    }

	    //This updates the screen with what has been drawn on the renderer
	    SDL_RenderPresent(display.getRenderer());
	    
	    //hud.disp();
	    //We have a blanket delay since the game is not intensive on any semi-modern system
	    //One day we'll intelligently set the framerate
	    //SDL_Delay(40);

	    // end updates
	} //end while 
    } //end else 
    display.close();
    return (0);
}//end run
