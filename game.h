// game.h
// Alex Rutan
// 4/1/15

#ifndef GAME_EXIST
#define GAME_EXIST

#include <SDL2/SDL.h>
#include <vector>
#include "game.h"

class Game
{
    private:
        int resX;
        int resY;
        SDL_Window* window;
	SDL_Surface* surface;
        SDL_Renderer* renderer;
	SDL_Texture* playerTexture;

    public:
        Game();
        ~Game();
        bool init();
	bool loadTextures();
        int run();
        void close();
}; //end Game

#endif //GAME_EXISTS
