#include "Player.h"

Player::Player(IntVector2 position, IntVector2 size, int maxX, int maxY)
{
   this->maxX = maxX;
   this->maxY = maxY;
   this->pos = position;
   this->size = size;
   this->speed = 10;
   this->rect = new RECT{
      (LONG)(pos.x - size.x*0.5f),
      (LONG)(pos.y - size.y*0.5f),
      (LONG)(pos.x + size.x*0.5f),
      (LONG)(pos.y + size.y*0.5f) };
}

Player::~Player()
{
   delete rect;
}

void Player::Update()
{
   if(pos.x + dir > 0 + size.x * 0.5f &&
      pos.x + dir < maxX - size.x * 0.5f)
   pos.x += dir;

   rect->left = (LONG)(pos.x - size.x * 0.5f);
   rect->top = (LONG)(pos.y - size.y * 0.5f);
   rect->right = (LONG)(pos.x + size.x * 0.5f);
   rect->bottom = (LONG)(pos.y + size.y * 0.5f);
}

void Player::Draw(HDC hdc, HBRUSH hbr)
{
   FillRect(hdc, rect, hbr);
}

void Player::Move(int xMovement)
{
   this->dir = xMovement * speed;
}

Projectile* Player::Shoot()
{
   return new Projectile(pos, IntVector2{ 2, 7 }, -1 * 7, maxY);
}

RECT* Player::GetRect()
{
   return rect;
}