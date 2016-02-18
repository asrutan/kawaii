// world.cpp
// Alex Rutan
// 11/22/15
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "world.h"
#include "tile.h"

using namespace std;

World::World()
{
    //not used
} //end constructor

World::World(Display* d)
{   
    //tiles = new Tile[12];
    Tile t;
    int xOffset = t.getTileWidth()/2;
    int yOffset = t.getTileHeight()/2;
    for(int i = 0; i < 12; i++)
    {
        //cout << i << endl;
	//tiles[i] = Tile(&display, (i * (xOffset * 2)/* + xOffset*/), (i * (yOffset * 2)/* - yOffset*/));//Makes stairway of tiles across screen
	//tiles[i] = Tile(&display, 0, 0);//Puts all tiles in same spot
	//tiles[i] = Tile(&display, (i * (xOffset * 2)/* + xOffset*/), 0/*(i * (yOffset * 2)/* - yOffset)*/);//Makes line of tiles across top of screen
	tiles.push_back(Tile(d, 0/*(i * (xOffset * 2)/* + xOffset)*/,(i * (yOffset * 2)/* - yOffset*/), 1));//Makes line of tiles across left-hand side of screen
    }//end for
    tiles.push_back(Tile(d,50,(12*50), 1));
    tiles.push_back(Tile(d,100,(12*50), 1));
}

World::World(Display* d, string fileName)
{
    loadWorld(fileName, d);
}

World::~World()
{
} //end destructor

Tile* World::getIthTile(int i)
{
    return &tiles[i];
}

int World::getTileCount()
{
    return tiles.size();
}

int World::stringToInt(string str)
{
    //Turns a String into an int
    stringstream ss(str);
    int returnVal;
    ss >> returnVal;
    return returnVal;
}

void World::loadWorld(string fileName, Display* d)
{
    //Expects a file formatted using # as comments (if needed). First two lines are width of world and height of world respectivly.
    ifstream file;
    file.open(fileName.c_str());//open file

    int worldWidth = -1;
    int worldHeight = -1;

    //*** 1st Column gets shifted up by one.*** 

    if(file.is_open())
    {
	string data;

	bool keepGoing = true;
	while(keepGoing)
	{
	    getline(file, data);
	    
	    if(data[0] == '#')//comment line
	    {
		//'#' is a comment in the map. Hopefully won't be needed when we get the map editor made.
	       
	    }//end comment if
	    else if(data.empty())//empty line
	    {

	    }
	    else //line with data
	    {
		if(worldWidth == -1)
		{
		    worldWidth = stringToInt(data);//first useable line of file is total width of the World
		    getline(file,data);
		    worldHeight = stringToInt(data);//second line is total world Height
		    keepGoing = false;
		}
	    }
	}//end while get Width & Height loop

	if(worldWidth == -1 || worldHeight == -1)
	{
	    cout << "Map File Corrupted (Couldn't read Map)" << endl;
	}
	else
	{
	    while(!file.eof())
	    {	
		//LOADSCREEN? use WW * WH as total? use itorator to pass progress to LoadScreen Class?
		for(int row = 0; row < worldHeight; row ++)
		{
		    for(int col = 0; col < worldWidth; col ++)
		    {
			getline(file,data,',');//keeps newline. WHY?
			//cout << "row: " << row << " col: " << col << " tag: " << data << endl;
			//cout << data.size() << endl;
			bool newLineChar = false;
			int index;
			for(int strSize = 0; strSize < data.size(); strSize ++)//if string longer than 1 char. In first file read: caused by newline character
			{
			    if(data[strSize] == '\n' || data[strSize] == '\r' || data[strSize] == '\r\n')//check all newline charachters
			    {
				//cout << "found" << endl;
				newLineChar = true;
				index = strSize;
			    }
			}//end multi char data for
			
			if(newLineChar)
			{
			    string temp = data.substr(0,index);//get first char
			    //cout << index << endl; 
			    //cout << "Temp: " << temp << endl;
			    bool keepGoing = true;
			    while(keepGoing)
			    {
				//cout << "in while" << endl;
				if(temp == "#")
				{

				}
				else if(temp == "1")
				{
				    tiles.push_back(Tile(d, col * 50, row * 50, 1));
				}
				else if(temp == "2")
				{
				    tiles.push_back(Tile(d, col * 50, row * 50, 2));
				    //player position?
				}
				//3 = enemies?
				//4 = ??
				//...
				
				data = data.substr(index);
				temp = data;
				col = 0;
				if(temp.size() == 0)
				{
				    row++;
				    //col = 0;
				    keepGoing = false;
				}
				//cout << temp.size() << endl;
			    }//end temp while
			    //cout << "Data: " << data << endl;
			}//end newLineChar if

			else if(data[0] == '#')
			{
			    //cout << "Comment" << endl;
			}//end comment check
			else if(data.empty())
			{
			    //cout << "in here" << endl;
			}//end empty check
			else
			{
			    if(data == "1")
			    {
				tiles.push_back(Tile(d, col * 50, row * 50, 1));
			    }
			    else if(data == "2")
			    {
				tiles.push_back(Tile(d, col * 50, row * 50, 2));
				//player position?
			    }
			    //3 = enemies?
			    //4 = ??
			    //...
			}
			
		    }//end col check
		}//end row check
	    }//end while
	    tiles.push_back(Tile(d,0,(worldHeight - 1) * 50, 1));//added to bottom left corner. missing b/c of upward shift issue.
	}//end read width & height check
    }
    else
    {
	cout << "Map not found." << endl;
    }
}
