#include "Projectile.h"

Projectile::Projectile(IntVector2 position, IntVector2 size, int direction, int maxY)
{
   deleteThis = false;
   this->maxY = maxY;
   this->pos = position;
   this->size = size;
   this->dir = direction;
   this->rect = new RECT{
      (LONG)(pos.x - size.x*0.5f),
      (LONG)(pos.y - size.y*0.5f),
      (LONG)(pos.x + size.x*0.5f),
      (LONG)(pos.y + size.y*0.5f) };
}

Projectile::~Projectile()
{
   delete rect;
}

void Projectile::Update()
{
   pos.y += dir;

   if (pos.y + size.y * 0.5f < 0 ||
      pos.y - size.y * 0.5f > maxY)
      deleteThis = true;

   rect->left = (LONG)(pos.x - size.x * 0.5f);
   rect->top = (LONG)(pos.y - size.y * 0.5f);
   rect->right = (LONG)(pos.x + size.x * 0.5f);
   rect->bottom = (LONG)(pos.y + size.y * 0.5f);
}

void Projectile::Draw(HDC hdc, HBRUSH hbr)
{
   FillRect(hdc, rect, hbr);
}

RECT* Projectile::GetRect()
{
   return rect;
}