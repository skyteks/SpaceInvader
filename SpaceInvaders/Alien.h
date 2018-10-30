#pragma once
#include "Global.h"
#include "Projectile.h"

class Alien
{
public:
   Alien(IntVector2 position, IntVector2 size, int maxX, int points);
   ~Alien();
   void Update(IntVector2 dir);
   void Draw(HDC hdc, HBRUSH hbr);
   IntVector2  GetPos();
   RECT* GetRect();
   int GetPoints();
private:
   int maxX;
   RECT* rect;
   IntVector2 size;
   IntVector2 pos;
   UINT points; // number * 10 = points
   int state;
};
