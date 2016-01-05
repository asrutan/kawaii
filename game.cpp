// game.cpp
// Alex Rutan
// 4/1/15
#include <iostream>
#include <sstream>
#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <string>
#include "game.h"
#include "hud.h"
#include "player.h"
#include "enemy.h"
#include "display.h"
#include "texture.h"
#include "textTexture.h"
#include "world.h"
#include "camFocus.h"
#include "background.h"

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
    enemyTexture = Texture(&display);
    backgroundTexture = Texture(&display);
    font = textTexture(&display);
    world = World(&display, "map.kwi");
    player = Player();
    enemy = Enemy();
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

    if(!enemyTexture.makeTexture("enemy.gif"))
    {
	cout << "Enemy texture failed, son" << endl;
	success = false;
    } //end if

    if(!backgroundTexture.makeTexture("background.gif"))
    {
	cout << "background texture failed my man" << endl;
	success = false;
    } //end if

    else
    
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
    //Collision collision = Collision(&player, &enemy, &world);
    Collision collision = Collision(&world);
    Hud hud;
    camFocus cam = camFocus(&player, &enemy, &world);
    //hud.init(&playerx);

    player.x = 100;
    player.y = 2300;

    enemy.x = 200;
    enemy.y = 2300;

    background.x = 0;
    background.y = 1500;

    //find a way to get this shit in player or something
    SDL_Rect srcPlayerRect;
    SDL_Rect dstPlayerRect;
    srcPlayerRect.x = 0;
    srcPlayerRect.y = 0;
    //srcPlayerRect.y = 137;
    srcPlayerRect.w = 100;
    srcPlayerRect.h = 136;
    dstPlayerRect.x = player.x;
    dstPlayerRect.y = player.y;
    dstPlayerRect.w = 100;
    dstPlayerRect.h = 136;

    SDL_Rect srcEnemyRect;
    SDL_Rect dstEnemyRect;
    srcEnemyRect.x = 0;
    srcEnemyRect.y = 0;
    //srcEnemyRect.y = 137;
    srcEnemyRect.w = 100;
    srcEnemyRect.h = 136;
    dstEnemyRect.x = enemy.x;
    dstEnemyRect.y = enemy.y;
    dstEnemyRect.w = 100;
    dstEnemyRect.h = 136;

    SDL_Rect srcBackgroundRect;
    SDL_Rect dstBackgroundRect;
    srcBackgroundRect.x = 0;
    srcBackgroundRect.y = 0;
    srcBackgroundRect.w = 1920;
    srcBackgroundRect.h = 1200;
    dstBackgroundRect.x = background.x;
    dstBackgroundRect.y = background.y;
    dstBackgroundRect.w = 1920;
    dstBackgroundRect.h = 1200;


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
	    player.update(); //update player
	    if(player.animForward)
	    {
		srcPlayerRect.y = 0;
	    } //end if
	    else if(player.animBackward)
	    {
		srcPlayerRect.y = 137;
	    } //end elif
	    else if(player.animIdle)
	    {
		srcPlayerRect.y = 273;
	    } //end else

	    if(!player.animIdle)
	    {
		if(player.frame < 1 && player.animForward)
		{
		    srcPlayerRect.x = 0;
		} //end if
		else if(player.frame == 1)
		{
		    srcPlayerRect.x = 100;
		} //end if
		else if(player.frame == 2)
		{
		    srcPlayerRect.x = 200;
		} //end if
		else if(player.frame == 3)
		{
		    srcPlayerRect.x = 300;
		} //end if
		else if(player.frame == 4)
		{
		    srcPlayerRect.x = 400;
		} //end if
		else if(player.frame == 5)
		{
		    srcPlayerRect.x = 500;
		} //end if
		else if(player.frame == 6)
		{
		    srcPlayerRect.x = 600;
		} //end if
		else if(player.frame == 7)
		{
		    srcPlayerRect.x = 700;
		} //end if */
		
		if(player.frame < 1 && player.animBackward)
		{
		    srcPlayerRect.x = 700;
		} //end if
		else if(player.frame == 1)
		{
		    srcPlayerRect.x = 600;
		} //end if
		else if(player.frame == 2)
		{
		    srcPlayerRect.x = 500;
		} //end if
		else if(player.frame == 3)
		{
		    srcPlayerRect.x = 400;
		} //end if
		else if(player.frame == 4)
		{
		    srcPlayerRect.x = 300;
		} //end if
		else if(player.frame == 5)
		{
		    srcPlayerRect.x = 200;
		} //end if
		else if(player.frame == 6)
		{
		    srcPlayerRect.x = 100;
		} //end if
		else if(player.frame == 7)
		{
		    srcPlayerRect.x = 0;
		} //end if
	    } //end if
	    else
	    {
		srcPlayerRect.x = 0;
	    } //end else

	    enemy.update(); //update enemy

	    if(enemy.frame < 1)
	    {
		srcEnemyRect.x = 0;
	    } //end if
	    else if(enemy.frame == 1)
	    {
		srcEnemyRect.x = 100;
	    } //end if
	    else if(enemy.frame == 2)
	    {
		srcEnemyRect.x = 200;
	    } //end if
	    else if(enemy.frame == 3)
	    {
		srcEnemyRect.x = 300;
	    } //end if
	    else if(enemy.frame == 4)
	    {
		srcEnemyRect.x = 400;
	    } //end if
	    else if(enemy.frame == 5)
	    {
		srcEnemyRect.x = 500;
	    } //end if
	    else if(enemy.frame == 6)
	    {
		srcEnemyRect.x = 600;
	    } //end if
	    else if(enemy.frame == 7)
	    {
		srcEnemyRect.x = 700;
	    } //end if */

	    collision.playerWallCollision(&player); //for player
	    player.move();
	    collision.checkFloorCollision(&player); //for player
	    //player.move();
	    
	    collision.playerWallCollision(&enemy); //for enemy
	    enemy.move();
	    collision.checkFloorCollision(&enemy); //for enemy
	    
	    //player.move();
	    if(player.quit)
	    {
		keepGoing = false;
	    } //end if
	    
	    cam.update(); //update camera

	    for(int i = 0; i < world.getTileCount(); i++)
	    {
	        //MOVE TO GLOBAL RENDER CLASS?
	        //Change destination to draw to based on player movement:
	        dstTileRects[i].x = world.getIthTile(i)->getXPos() - cam.x;
		//cout << world.getIthTile(i)->getXPos() << endl;
	        dstTileRects[i].y = world.getIthTile(i)->getYPos() - cam.y;
	        //cout << tiles[i].getXPos() << endl;
	    }

	    dstPlayerRect.x = player.x - cam.x;
	    dstPlayerRect.y = player.y - cam.y;

	    dstEnemyRect.x = enemy.x - cam.x;
	    dstEnemyRect.y = enemy.y - cam.y;

	    dstBackgroundRect.x = background.x - cam.x;
	    dstBackgroundRect.y = background.y - cam.y;

	    SDL_UpdateWindowSurface(display.getWindow());	
	    SDL_SetRenderDrawColor(display.getRenderer(), 80, 80, 80, 255);
	    SDL_RenderClear(display.getRenderer());		 

            SDL_SetRenderDrawColor(display.getRenderer(), 200, 200, 200, 255);	    

            SDL_SetRenderDrawColor(display.getRenderer(), 255,255,255,255);
            //SDL_RenderCopy(renderer, textTexture, NULL, NULL);

	    SDL_RenderCopy(display.getRenderer(), backgroundTexture.getTexture(), &srcBackgroundRect, &dstBackgroundRect); //draw background

	    stringstream strs;
	    strs << "X: " << player.x << "  Y: " << player.y << "Pixels";
	    string str = strs.str();

	    for(int k = 0; k < world.getTileCount(); k++)
	    {
	      SDL_RenderCopy(display.getRenderer(), world.getIthTile(k)->getTexture(), &srcTileRects[k], &dstTileRects[k]);
	    } //draw tiles

	    SDL_RenderCopy(display.getRenderer(), enemyTexture.getTexture(), &srcEnemyRect, &dstEnemyRect); //draw enemy

	    SDL_RenderCopy(display.getRenderer(), playerTexture.getTexture(), &srcPlayerRect, &dstPlayerRect); //draw player

	    font.loadFontFromRenderedText(str, {50, 50, 225}); //draw text?
	    font.renderTextTexture((display.getResX() - font.getFontFileWidth()) / 2, 550); //draw text

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
