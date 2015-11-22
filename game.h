// game.h
// Alex Rutan
// 4/1/15

#ifndef GAME_EXIST
#define GAME_EXIST

#include <SDL2/SDL.h>
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"
#include <string.h>
#include <vector>
#include "game.h"
#include "display.h"
#include "texture.h"
#include "textTexture.h"

using namespace std;

class Game
{
    private:
        //int resX;
        //int resY;
        //SDL_Window* window;
	//SDL_Surface* surface;
        //SDL_Renderer* renderer;
	//SDL_Texture* playerTexture;
	//SDL_Texture* textTexture;
	//TTF_Font* textFont;
	//int textWidth;
	//int textHeight;
        Display display;
	Texture player;
	textTexture font;

    public:
        Game();
        ~Game();
        //bool init();
	bool loadTextures();
        int run();
        //void close();

	//bool loadFontMedia();
	//bool loadFontFromFile(string);
	//bool loadFontFromRenderedText(string, SDL_Color);
	//void releaseTextTexture();
	//void setColor(Uint8, Uint8, Uint8);
	//void setBlendMode(SDL_BlendMode);
	//void setAlpha(Uint8);
	//void renderTextTexture(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	//int getFontFileWidth();
	//int getFontFileHeight();
}; //end Game

#endif //GAME_EXISTS
