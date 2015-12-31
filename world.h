// world.h
// Alex Rutan
// 11/22/15

#ifndef WORLD_EXIST
#define WORLD_EXIST

#include <vector>
#include <string>
#include "tile.h"

class World
{
    private:
	std::vector<Tile> tiles;
	int stringToInt(std::string);

    public:
        World();
	World(Display*);
	World(Display*, std::string);
        ~World();
	Tile* getIthTile(int);
	int getTileCount();
	void loadWorld(std::string, Display*);
}; //end World(lol)

#endif //WORLD_EXISTS
