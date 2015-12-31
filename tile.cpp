//tile.cpp
//PA
//11/22/15

#include <iostream>
#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"
#include <string>
#include "display.h"
#include "texture.h"
#include "tile.h"
#include "collideBox.h"

using namespace std;

Tile::Tile()
{
    myTexture = NULL;
    tileW = 50;
    tileH = 50;
    posX = 0;
    posY = 0;
    cBox = collideBox(posX, posX + tileW, posY, posY + tileH);
}

Tile::Tile(Display* d, int x, int y)
{
    display = d;
    tileW = 50;
    tileH = 50;
    posX = x;
    posY = y;
    texture = Texture(display);
    cBox = collideBox(posX, posX + tileW, posY, posY + tileH);
    myTexture = NULL;
}

Tile::~Tile()
{
}

int Tile::getTileWidth()
{
    return tileW;
}

int Tile::getTileHeight()
{
    return tileH;
}

int Tile::getXPos()
{
    return posX;
}

void Tile::setXPos(int x)
{
    posX = x;
}

void Tile::setYPos(int y)
{
    posY = y;
}

int Tile::getYPos()
{
    return posY;
}

collideBox Tile::getCollideBox()
{
    return cBox;
}

bool Tile::textureTile(string path)
{
    bool success = true;
    if(!texture.makeTexture(path))
    {
	success = false;
    }
    else
    {
        myTexture = texture.getTexture();
    }
    //cout << success << endl;
    return success;
}

SDL_Texture* Tile::getTexture()
{
    return myTexture;
}
