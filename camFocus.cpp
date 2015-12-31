// camFocus.cpp
// Alex Rutan
// 12/1/15

#include "camFocus.h"
#include "player.h"
#include "world.h"

using namespace std;

camFocus::camFocus()
{
    *player = Player();
    *world = World();
    xTarget = 0; //make target an array (not xtarg ytarg i'm just leaving this here for future reference)
    yTarget = 0;
    xVelocity = 0;
    yVelocity = 0;
    x = 0;
    y = 0;
} // end constructor

camFocus::camFocus(Player* p, World* w)
{
    xTarget = 0; //make target an array (not xtarg ytarg i'm just leaving this here for future reference)
    yTarget = 0;
    xVelocity = 0;
    yVelocity = 0;
    x = 0;
    y = 0;
    player = p;
    world = w;
    campan = true;
} //end camFocus args

camFocus::~camFocus()
{    
} //end destructor

void camFocus::move()
{
    if(x == -50)
    {
	campan = false;
    }
    if(x == 50)
    {
	campan = true;
    } //end else */
    
    if(campan)
    {
        x--;
        y--;
    }
    if(campan)
    {
	x++;
        y++;
    }
} //end move
void camFocus::update()
{
    x = player->x - 400;
    y = player->y - 300;
} //end update

/*camFocus::switch(target)
{

} //end switch
*/

