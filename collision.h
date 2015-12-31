// collision.h
// PA
// 12/01/15

#ifndef COLLISION_EXIST
#define COLLISION_EXIST

#include "player.h"
#include "world.h"
#include "collideBox.h"

class Collision
{
  private:
    Player* player;
    World* world;
    int playerX;
    int playerY;
  public:
    Collision();
    Collision(Player*, World*);
    ~Collision();
    void playerWallCollision(collideBox);
    void checkFloorCollision(collideBox);
    
};

#endif
