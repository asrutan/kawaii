// camFocus.cpp
// Alex Rutan
// 12/1/15

#include "camFocus.h"
#include "player.h"
#include "enemy.h"
#include "world.h"

using namespace std;

camFocus::camFocus()
{
    *player = Player();
    *enemy = Enemy();
    *world = World();
    xTarget = 0; //make target an array (not xtarg ytarg i'm just leaving this here for future reference)
    yTarget = 0;
    xVelocity = 0;
    yVelocity = 0;
    x = 0;
    y = 0;
} // end constructor

camFocus::camFocus(Player* p, Enemy* e, World* w)
{
    xTarget = 0; //make target an array (not xtarg ytarg i'm just leaving this here for future reference)
    yTarget = 0;
    xVelocity = 0;
    yVelocity = 0;
    x = 0;
    y = 0;
    player = p;
    enemy = e;
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
    x = player->x - 350;
    y = player->y - 400;
} //end update

/*camFocus::switch(target)
{

} //end switch
*/

