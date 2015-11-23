// world.h
// Alex Rutan
// 11/22/15

#ifndef WORLD_EXIST
#define WORLD_EXIST

class World
{
    private:
        int ground1;
	int ground2;
	int ground3;
	int wall1x;
	int wall1y1;
	int wall1y2;

    public:
        World();
        ~World();
	int getGround(int);
	int regionRange(int);
}; //end World(lol)

#endif //WORLD_EXISTS
