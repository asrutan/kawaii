//dispay.h
//Alex Rutan / PA
//11/22/15

#ifndef DISPLAY_EXIST
#define DISPLAY_EXIST

#include <SDL2/SDL.h>

class Display
{
    private:
        int resX;
        int resY;
        SDL_Window* window;
	SDL_Surface* surface;
        SDL_Renderer* renderer;

    public:
	Display();
	~Display();
	bool init();
	void close();
	SDL_Renderer* getRenderer();
	SDL_Window* getWindow();
	bool loadTextures();

	int getResX();
	int getResY();
};

#endif
