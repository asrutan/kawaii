// game.h
// Alex Rutan
// 4/1/15

#ifndef GAME_EXIST
#define GAME_EXIST

#include <SDL2/SDL.h>
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"
#include <string.h>
#include "display.h"
#include "texture.h"
#include "textTexture.h"
#include "tile.h"

class Game
{
    private:
        Display display;
	Texture player;
	textTexture font;
	Tile* tiles;

    public:
        Game();
        ~Game();
	bool loadTextures();
        int run();
        
}; //end Game

#endif //GAME_EXISTS
