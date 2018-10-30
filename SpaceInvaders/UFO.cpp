#include "UFO.h"

UFO::UFO(IntVector2 position, IntVector2 size)
{
   this->pos = position;
   this->size = size;
   this->rect = new RECT{
      (LONG)(pos.x - size.x*0.5f),
      (LONG)(pos.y - size.y*0.5f),
      (LONG)(pos.x + size.x*0.5f),
      (LONG)(pos.y + size.y*0.5f) };
}

UFO::~UFO()
{
   delete rect;
}

void UFO::Update(int dir)
{
   pos.x += dir;

   rect->left = (LONG)(pos.x - size.x * 0.5f);
   rect->top = (LONG)(pos.y - size.y * 0.5f);
   rect->right = (LONG)(pos.x + size.x * 0.5f);
   rect->bottom = (LONG)(pos.y + size.y * 0.5f);
}

void UFO::Draw(HDC hdc, HBRUSH hbr)
{
	for (int x = 0; x < 16; x++)
	{
		for (int y = 0; y < 7; y++)
		{
			if (
				(x == 0 && y == 0) ||//left head side
				(x == 1 && y == 0) ||
				(x == 2 && y == 0) ||
				(x == 3 && y == 0) ||
				(x == 4 && y == 0) ||
				(x == 5 && y == 0) ||
				(x == 0 && y == 1) ||
				(x == 1 && y == 1) ||
				(x == 2 && y == 1) ||
				(x == 0 && y == 2) ||
				(x == 1 && y == 2) ||
				(x == 0 && y == 3) ||

				(x == 10 && y == 0) ||//right head side
				(x == 11 && y == 0) ||
				(x == 12 && y == 0) ||
				(x == 13 && y == 0) ||
				(x == 14 && y == 0) ||
				(x == 15 && y == 0) ||
				(x == 13 && y == 1) ||
				(x == 14 && y == 1) ||
				(x == 15 && y == 1) ||
				(x == 14 && y == 2) ||
				(x == 15 && y == 2) ||
				(x == 15 && y == 3) ||

				(x == 3 && y == 3) ||//eyes
				(x == 5 && y == 3) ||
				(x == 7 && y == 3) ||
				(x == 9 && y == 3) ||

				(x == 0 && y == 5) ||//left arm side
				(x == 1 && y == 5) ||
				(x == 0 && y == 6) ||
				(x == 1 && y == 6) ||
				(x == 2 && y == 6) ||

				(x == 14 && y == 5) ||//right arm side
				(x == 15 && y == 5) ||
				(x == 13 && y == 6) ||
				(x == 14 && y == 6) ||
				(x == 15 && y == 6) ||

				(x == 5 && y == 5) ||//space between arms
				(x == 6 && y == 5) ||
				(x == 9 && y == 5) ||
				(x == 10 && y == 5) ||
				(x == 4 && y == 6) ||
				(x == 5 && y == 6) ||
				(x == 6 && y == 6) ||
				(x == 7 && y == 6) ||
				(x == 8 && y == 6) ||
				(x == 9 && y == 6) ||
				(x == 10 && y == 6) ||
				(x == 11 && y == 6))
			{
			}
			else
				SetPixel(hdc, pos.x + x - 12, pos.y + y - 3, RGB(255, 0, 0));
		}
	}
}

IntVector2 UFO::GetPos()
{
   return pos;
}

RECT* UFO::GetRect()
{
    return rect;
}

int UFO::GetPoints()
{
   return (rand() % 3 + 1) * 50;
}