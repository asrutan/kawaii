// texture.cpp
// Alex Rutan / PA
// 11/22/15
#include <iostream>
#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <string.h>
#include <cmath>
#include "display.h"
#include "texture.h"

using namespace std;

Texture::Texture()
{
    //Not used
    ground = 500;
    surface = NULL;
    texture = NULL;
}

Texture::Texture(Display* d)
{
    display = d;

    ground = 500;
    surface = NULL;
    texture = NULL;
} //end constructor

Texture::~Texture()
{
} //end destructor

bool Texture::makeTexture(string path)
{
    bool success = true;
    surface = SDL_LoadBMP(path.c_str());
    if(surface == NULL)
    {
        cout << "Couldn't load " << path << endl;
	cout << SDL_GetError() << endl;
	success = false;
    } //end if
    else
    {
        texture = SDL_CreateTextureFromSurface(display->getRenderer(), surface);
	if(texture == NULL)
	{
	    success = false;
	} //end if
    } //end else
    return success;
} //end loadTextures

SDL_Texture* Texture::getTexture()
{
    return texture;
}

