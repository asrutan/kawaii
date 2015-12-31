// game.h
// Alex Rutan
// 4/1/15

#ifndef GAME_EXIST
#define GAME_EXIST

#include <SDL2/SDL.h>
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"
#include <string>
#include "display.h"
#include "texture.h"
#include "textTexture.h"
#include "tile.h"
#include "world.h"
#include "player.h"
#include "collision.h"

class Game
{
    private:
        Display display;
	Texture playerTexture;
	textTexture font;
	//Tile* tiles;
	World world;
	Player player;
	//Collision collision;

    public:
        Game();
        ~Game();
	bool loadTextures();
        int run();
        
}; //end Game

#endif //GAME_EXISTS
