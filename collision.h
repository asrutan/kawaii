// collision.h
// PA
// 12/01/15

#ifndef COLLISION_EXIST
#define COLLISION_EXIST

#include "player.h"
#include "enemy.h"
#include "world.h"
#include "entity.h"

class Collision
{
  private:
    Player* player;
    Enemy* enemy;
    World* world;
    int playerX;
    int playerY;
  public:
    Collision();
    Collision(Player*, Enemy*, World*);
    Collision(World*);
    ~Collision();
    void playerWallCollision(Entity*);
    void checkFloorCollision(Entity*);
    
};

#endif
