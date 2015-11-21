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
        double playerx;
	double playery;
	int playerDir;
	double dx;
	double dy;
	double wallx1;
	double wally1;
	double wallx2;
	double wally2;
	double twx1;
	double twx2;
	double twy1;
	double twy2;
	double twz1;
	double twz2;

    public:
        Game();
        ~Game();
        bool init();
        int run();
        void close();
        void rotate(bool);
}; //end Game

#endif //GAME_EXISTS
