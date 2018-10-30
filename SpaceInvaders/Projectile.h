#pragma once
#include "Global.h"

class Projectile
{
public:
   Projectile(IntVector2 position, IntVector2 size, int direction, int maxY);
   ~Projectile();
   void Update();
   void Draw(HDC hdc, HBRUSH hbr);
   RECT* GetRect();
   bool deleteThis;
private:
   int dir;
   int maxY;
   IntVector2 pos;
   IntVector2 size;
   RECT* rect;
};