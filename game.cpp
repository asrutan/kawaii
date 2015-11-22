// game.cpp
// Alex Rutan
// 4/1/15
#include <iostream>
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

using namespace std;

/*
Game constructor 
defines the values used for the resolution of the screen
initializes values used by SDL for renderer, window, and textures
 */
Game::Game()
{
  /*resX = 800;
    resY = 600;
    window = NULL;
    surface = NULL;
    renderer = NULL;
    playerTexture = NULL;

    textTexture = NULL;
    textFont = NULL;
    textWidth = 0;
    textHeight = 0;*/
    //display.init();
    player = Texture(&display);
    font = textTexture(&display);
} //end constructor

Game::~Game()
{
} //end destructor


/*NOW IN Display.cpp
Initializes SDL and creates window, renderer, and assigns values for their initialization
Has checks to make sure everythin initializes properly
Otherwise it would be very hard to pinpoint what is breaking when nothing happens
 */
/*bool Game::init()
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
} //end init*/


bool Game::loadTextures()
{
    bool success = true;
    if(!player.makeTexture("player.bmp"))
    {
	success = false;
    }
    if(!font.loadFontMedia("/usr/share/fonts/truetype/fonts-japanese-gothic.ttf"))
    {
	success = false;
    }
    /*NOW IN Texture.cpp
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
    */
    return success;
} //end loadTextures


/*NOW IN Display.cpp
Destroy each of the textures, surface, window, and renderer
Otherwise things hang around in memory
Execute "SDL_Quit()" to properly close SDL
 */
/*NOW IN Display.cpp
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
    TTF_Quit();
    IMG_Quit();
} //end close
*/

/*NOW IN textTexture.cpp
bool Game::loadFontMedia()
{
    //Loading success flag
    bool success = true;
    //cout << "About to load font" << endl;
    //Open the font
    textFont = TTF_OpenFont("/usr/share/fonts/truetype/fonts-japanese-gothic.ttf", 28);
    if(textFont == NULL)
    {
        cout << "Failed to load font! SDL_ttf Error: " << '\n' <<  TTF_GetError() << endl;
       	success = false;
    }
    else
    {
        //cout << "Font Loaded" << endl;
       	//Render text
       	SDL_Color textColor = { 225, 225, 225 };
       	if(!loadFontFromRenderedText("Madoka 4 lyfe!!", textColor))
	{
  	    cout << "Failed to render text texture!\n" << endl;
       	    success = false;
       	}
    }

    return success;
}
*/

/*NOW IN textTexture.cpp
bool Game::loadFontFromRenderedText(string textAsTexture, SDL_Color textColor)
{
    //Get rid of existing texture
    releaseTextTexture();

    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(textFont, textAsTexture.c_str(), textColor);
    if(textSurface == NULL)
    {
        //cout << "Surface not Made" << endl;
        cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << endl;
    }
    else
    {
        //cout << "Surface made" << endl;
        //Create texture from surface pixels
	textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if(textTexture == NULL)
        {
            cout << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << endl;
        }
        else
        {
	    //cout << "Texture made" << endl;
   	    //Get image dimensions
       	    textWidth = textSurface->w;
	    textHeight = textSurface->h;
	    //cout << textWidth << endl;
	    //cout << textHeight << endl;
	}

       	//Get rid of old surface
       	SDL_FreeSurface(textSurface);
	}
	
    //Return success
    return textTexture != NULL;
}

void Game::releaseTextTexture()
{
    //Free texture if it exists
    if(textTexture != NULL)
    {
        SDL_DestroyTexture(textTexture);
       	textTexture = NULL;
       	textWidth = 0;
       	textHeight = 0;
    }
}

void Game::renderTextTexture(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = {x, y, textWidth, textHeight};

    //Set clip rendering dimensions
    if(clip != NULL)
    {
      	renderQuad.w = clip->w;
       	renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopyEx(renderer, textTexture, clip, &renderQuad, angle, center, flip);
    //SDL_RenderCopy(renderer, textTexture, NULL, NULL);
}

int Game::getFontFileWidth()
{
    return textWidth;
}
int Game::getFontFileHeight()
{
    return textHeight;
}
*/

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

	    //cout << resX-(getFontFileWidth()/2) << endl;
	    //cout << resY-(getFontFileHeight()/2) << endl;

            SDL_SetRenderDrawColor(display.getRenderer(), 255,255,255,255);
            //SDL_RenderCopy(renderer, textTexture, NULL, NULL);
	    font.renderTextTexture((display.getResX() - font.getFontFileWidth()) / 2, 550);

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
