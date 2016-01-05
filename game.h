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
#include "enemy.h"
#include "collision.h"
#include "background.h"

class Game
{
    private:
        Display display;
	Texture playerTexture;
	Texture enemyTexture;
	Texture backgroundTexture;
	textTexture font;
	//Tile* tiles;
	World world;
	Player player;
	Enemy enemy;
	Background background;
	//Collision collision;

    public:
        Game();
        ~Game();
	bool loadTextures();
        int run();
        
}; //end Game

#endif //GAME_EXISTS
