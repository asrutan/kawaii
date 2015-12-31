// tile.h
// PA
// 11/22/15

#ifndef TILE_EXIST
#define TILE_EXIST

#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"
#include <string>
#include "display.h"
#include "texture.h"
#include "collideBox.h"

class Tile
{
    private:
       Texture texture;
       SDL_Texture* myTexture;
       Display* display;
       int tileW;
       int tileH;
       int posX;
       int posY;
       collideBox cBox;
    public:
       Tile();
       Tile(Display*, int, int);
       ~Tile();
       int getTileWidth();
       int getTileHeight();
       int getXPos();
       int getYPos();
       collideBox getCollideBox();
       void setXPos(int);
       void setYPos(int);
       bool textureTile(std::string);
       SDL_Texture* getTexture();
};

#endif
