#pragma once
#include "Global.h"
#include "Projectile.h"

class UFO
{
public:
   UFO(IntVector2 position, IntVector2 size);
   ~UFO();
   void Update(int dir);
   void Draw(HDC hdc, HBRUSH hbr);
   IntVector2  GetPos();
   RECT* GetRect();
   int GetPoints();
private:
   int maxX;
   RECT* rect;
   IntVector2 size;
   IntVector2 pos;
};
