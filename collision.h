// collision.h
// PA
// 12/01/15

#ifndef COLLISION_EXIST
#define COLLISION_EXIST

#include "world.h"
#include "entity.h"

class Collision
{
  private:
    World* world;
    int playerX;
    int playerY;
  public:
    Collision();
    Collision(World*);
    ~Collision();
    void playerWallCollision(Entity*);
    void checkFloorCollision(Entity*);
    
};

#endif
