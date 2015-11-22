// world.cpp
// Alex Rutan
// 11/22/15
#include <iostream>
#include <fstream>
#include <string>
#include "world.h"

using namespace std;

World::World()
{
    ground1 = 500;
    ground2 = 200;
    ground3 = 800;
    wall1x = 300;
    wall1y1 = 200;
    wall1y2 = 500;
    loadMap();
    //sectors[a1, a2, a3, a4, a5, a6, a7, a8]
} //end constructor

World::~World()
{
} //end destructor

void World::loadMap()
//read the file and count the lines to determine how
//large the array should be when created on the heap
{
    /*
    int i = -1;
    ifstream file;
    file.open("map.map");
    string item;
    while (!file.eof())
    {
	getline(file, item);
	if (item != "")
	{		
	    i++;
	} //end if
	else{
            cout << i << endl;
	} //end else
    } //end while
    file.close();
    */
} //end loadMap

int World::getGround(int playerX)
{
    return(regionRange(playerX));
} //end getGround

int World::regionRange(int playerX)
{
    if(playerX < 300)
    {
	return(ground1);
    } //end if
    else if(playerX > 300)
    {
	return(ground2);
    } //end else if
} //end regionRange
