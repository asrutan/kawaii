// texture.h
// Alex Rutan / PA
// 11/22/15

#ifndef TEXTURE_EXIST
#define TEXTURE_EXIST

#include "display.h"
#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"

class Texture
{
    private:
        int ground;
	Display* display;
	SDL_Surface* surface;
	SDL_Texture* texture;

    public:
	Texture();
        Texture(Display*);
        ~Texture();
	bool makeTexture(std::string);
	SDL_Texture* getTexture();
}; //end Texture

#endif //TEXTURE_EXISTS
