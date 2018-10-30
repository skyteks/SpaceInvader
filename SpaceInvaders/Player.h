#pragma once
#include "Global.h"
#include "Projectile.h"

class Player
{
public:
   Player(IntVector2 position, IntVector2 size, int maxX, int maxY);
   ~Player();
   void Update();
   void Draw(HDC hdc, HBRUSH hbr);
   void Move(int xMovement);
   Projectile* Shoot();
   RECT* GetRect();
private:
   int speed;
   int dir;
   int maxX;
   int maxY;
   IntVector2 pos;
   IntVector2 size;
   RECT* rect;
};