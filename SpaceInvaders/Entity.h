#pragma once
#include "Global.h"

class Entity
{
public:
   Entity();
   ~Entity();
   virtual void Update();
   virtual void Draw(HDC hdc, HBRUSH hbr);
private:
   int speed;
   IntVector2 pos;
   IntVector2 size;
};