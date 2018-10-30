#include "Alien.h"

Alien::Alien(IntVector2 position, IntVector2 size, int maxX, int points)
{
	this->points = points;
	this->maxX = maxX;
	this->pos = position;
	this->size = size;
	this->rect = new RECT{
	   (LONG)(pos.x - size.x*0.5f),
	   (LONG)(pos.y - size.y*0.5f),
	   (LONG)(pos.x + size.x*0.5f),
	   (LONG)(pos.y + size.y*0.5f) };
	this->state = 1;
}

Alien::~Alien()
{
	delete rect;
}

void Alien::Update(IntVector2 dir)
{
	pos.x += dir.x;
	pos.y += dir.y;

	rect->left = (LONG)(pos.x - size.x * 0.5f);
	rect->top = (LONG)(pos.y - size.y * 0.5f);
	rect->right = (LONG)(pos.x + size.x * 0.5f);
	rect->bottom = (LONG)(pos.y + size.y * 0.5f);
}

void Alien::Draw(HDC hdc, HBRUSH hbr)
{
	//FillRect(hdc, rect, hbr);
	if (state == 20)
		state = -20;
	else if (state == -1)
		state = 1;
	switch (points)
	{
	case 10:
		if (state > 0)
		{
			for (int x = 0; x < 12; x++)
			{
				for (int y = 0; y < 8; y++)
				{
					if (//arms out
						(x == 0 && y == 0) ||//left head side
						(x == 1 && y == 0) ||
						(x == 2 && y == 0) ||
						(x == 3 && y == 0) ||
						(x == 0 && y == 1) ||

						(x == 8 && y == 0) ||//right head side
						(x == 9 && y == 0) ||
						(x == 10 && y == 0) ||
						(x == 11 && y == 0) ||
						(x == 11 && y == 1) ||

						(x == 3 && y == 3) ||//eyes
						(x == 4 && y == 3) ||
						(x == 7 && y == 3) ||
						(x == 8 && y == 3) ||

						(x == 0 && y == 5) ||//left arm side
						(x == 1 && y == 5) ||
						(x == 2 && y == 5) ||
						(x == 0 && y == 6) ||
						(x == 1 && y == 6) ||

						(x == 9 && y == 5) ||//right arm side
						(x == 10 && y == 5) ||
						(x == 11 && y == 5) ||
						(x == 10 && y == 6) ||
						(x == 11 && y == 6) ||

						(x == 5 && y == 5) ||//space between arms
						(x == 6 && y == 5) ||
						(x == 4 && y == 6) ||
						(x == 7 && y == 6) ||
						(x == 2 && y == 7) ||
						(x == 3 && y == 7) ||
						(x == 4 && y == 7) ||
						(x == 5 && y == 7) ||
						(x == 6 && y == 7) ||
						(x == 7 && y == 7) ||
						(x == 8 && y == 7) ||
						(x == 9 && y == 7))
					{
					}
					else
						SetPixel(hdc, pos.x + x - 8, pos.y + y - 2, RGB(255, 255, 255));
				}
			}
		}
		else if (state < 0)
		{
			for (int x = 0; x < 12; x++)
			{
				for (int y = 0; y < 8; y++)
				{
					if (//arms in
						(x == 0 && y == 0) ||//left head side
						(x == 1 && y == 0) ||
						(x == 2 && y == 0) ||
						(x == 3 && y == 0) ||
						(x == 0 && y == 1) ||

						(x == 8 && y == 0) ||//right head side
						(x == 9 && y == 0) ||
						(x == 10 && y == 0) ||
						(x == 11 && y == 0) ||
						(x == 11 && y == 1) ||

						(x == 3 && y == 3) ||//eyes
						(x == 4 && y == 3) ||
						(x == 7 && y == 3) ||
						(x == 8 && y == 3) ||

						(x == 0 && y == 5) ||//left arm side
						(x == 1 && y == 5) ||
						(x == 0 && y == 6) ||
						(x == 0 && y == 7) ||
						(x == 1 && y == 7) ||

						(x == 10 && y == 5) ||//right arm side
						(x == 11 && y == 5) ||
						(x == 11 && y == 6) ||
						(x == 10 && y == 7) ||
						(x == 11 && y == 7) ||

						(x == 5 && y == 5) ||//space between arms
						(x == 6 && y == 5) ||
						(x == 3 && y == 6) ||
						(x == 4 && y == 6) ||
						(x == 7 && y == 6) ||
						(x == 8 && y == 6) ||
						(x == 4 && y == 7) ||
						(x == 5 && y == 7) ||
						(x == 6 && y == 7) ||
						(x == 7 && y == 7))
					{
					}
					else
						SetPixel(hdc, pos.x + x - 8, pos.y + y - 2, RGB(255, 255, 255));
				}
			}
		}
		break;
	case 20:
		if (state > 0)
		{
			for (int x = 0; x < 11; x++)
			{
				for (int y = 0; y < 8; y++)
				{
					if (//arms in
						(x == 0 && y == 0) ||//left head side
						(x == 1 && y == 0) ||
						(x == 0 && y == 1) ||
						(x == 1 && y == 1) ||
						(x == 2 && y == 1) ||
						(x == 0 && y == 2) ||
						(x == 1 && y == 2) ||
						(x == 0 && y == 3) ||

						(x == 9  && y == 0) ||//right head side
						(x == 10 && y == 0) ||
						(x == 8 && y == 1) ||
						(x == 9 && y == 1) ||
						(x == 10 && y == 1) ||
						(x == 9 && y == 2) ||
						(x == 10 && y == 2) ||
						(x == 10 && y == 3) ||

						(x == 3 && y == 0) ||//above head size
						(x == 4 && y == 0) ||
						(x == 5 && y == 0) ||
						(x == 6 && y == 0) ||
						(x == 7 && y == 0) ||
						(x == 4 && y == 1) ||
						(x == 5 && y == 1) ||
						(x == 6 && y == 1) ||

						(x == 3 && y == 3) ||//eyes
						(x == 7 && y == 3) ||

						(x == 1 && y == 5) ||//left arm side
						(x == 1 && y == 6) ||
						(x == 0 && y == 7) ||
						(x == 1 && y == 7) ||
						(x == 2 && y == 7) ||

						(x == 9 && y == 5) ||//right arm side
						(x == 9 && y == 6) ||
						(x == 8 && y == 7) ||
						(x == 9 && y == 7) ||
						(x == 10 && y == 7) ||

						(x == 3 && y == 6) ||//space between arms
						(x == 4 && y == 6) ||
						(x == 5 && y == 6) ||
						(x == 6 && y == 6) ||
						(x == 7 && y == 6) ||
						(x == 5 && y == 7))
					{
					}
					else
						SetPixel(hdc, pos.x + x - 7, pos.y + y - 2, RGB(255, 255, 255));
				}
			}
		}
		else if (state < 0)
		{
			for (int x = 0; x < 11; x++)
			{
				for (int y = 0; y < 8; y++)
				{
					if (//arms out
						(x == 0 && y == 0) ||//left head side
						(x == 1 && y == 0) ||
						(x == 1 && y == 1) ||
						(x == 2 && y == 1) ||
						(x == 1 && y == 2) ||

						(x == 9  && y == 0) ||//right head side
						(x == 10 && y == 0) ||
						(x == 8 && y == 1) ||
						(x == 9 && y == 1) ||
						(x == 10 && y == 2) ||

						(x == 3 && y == 0) ||//above head size
						(x == 4 && y == 0) ||
						(x == 5 && y == 0) ||
						(x == 6 && y == 0) ||
						(x == 7 && y == 0) ||
						(x == 4 && y == 1) ||
						(x == 5 && y == 1) ||
						(x == 6 && y == 1) ||

						(x == 3 && y == 3) ||//eyes
						(x == 7 && y == 3) ||

						(x == 0 && y == 5) ||//left arm side
						(x == 0 && y == 6) ||
						(x == 1 && y == 6) ||
						(x == 0 && y == 7) ||

						(x == 10 && y == 5) ||//right arm side
						(x == 9 && y == 6) ||
						(x == 10 && y == 6) ||
						(x == 10 && y == 7) ||

						(x == 3 && y == 6) ||//space between arms
						(x == 4 && y == 6) ||
						(x == 5 && y == 6) ||
						(x == 6 && y == 6) ||
						(x == 7 && y == 6) ||
						(x == 2 && y == 7) ||
						(x == 3 && y == 7) ||
						(x == 4 && y == 7) ||
						(x == 5 && y == 7) ||
						(x == 6 && y == 7) ||
						(x == 7 && y == 7) ||
						(x == 8 && y == 7))
					{
					}
					else
						SetPixel(hdc, pos.x + x - 7, pos.y + y - 2, RGB(255, 255, 255));
				}
			}
		}
		break;
	case 40:
		if (state > 0)
		{
			for (int x = 0; x < 8; x++)
			{
				for (int y = 0; y < 8; y++)
				{
					if (//arms out
						(x == 0 && y == 0) ||//left head side
						(x == 1 && y == 0) ||
						(x == 2 && y == 0) ||
						(x == 0 && y == 1) ||
						(x == 1 && y == 1) ||
						(x == 0 && y == 2) ||

						(x == 7 && y == 0) ||//right head side
						(x == 6 && y == 0) ||
						(x == 5 && y == 0) ||
						(x == 7 && y == 1) ||
						(x == 6 && y == 1) ||
						(x == 7 && y == 2) ||

						(x == 2 && y == 3) ||//eyes
						(x == 5 && y == 3) ||

						(x == 0 && y == 5) ||//left arm side
						(x == 1 && y == 5) ||
						(x == 0 && y == 6) ||

						(x == 7 && y == 5) ||//right arm side
						(x == 6 && y == 5) ||
						(x == 7 && y == 6) ||

						(x == 1 && y == 7) ||//space between arms
						(x == 3 && y == 7) ||
						(x == 4 && y == 7) ||
						(x == 3 && y == 5) ||
						(x == 4 && y == 5) ||
						(x == 2 && y == 6) ||
						(x == 5 && y == 6) ||
						(x == 6 && y == 7))
					{
					}
					else
						SetPixel(hdc, pos.x + x - 4, pos.y + y - 2, RGB(255, 255, 255));
				}
			}
		}
		else if (state < 0)
		{
			for (int x = 0; x < 8; x++)
			{
				for (int y = 0; y < 8; y++)
				{
					if (//arms in
						(x == 0 && y == 0) ||//left head side
						(x == 1 && y == 0) ||
						(x == 2 && y == 0) ||
						(x == 0 && y == 1) ||
						(x == 1 && y == 1) ||
						(x == 0 && y == 2) ||

						(x == 7 && y == 0) ||//right head side
						(x == 6 && y == 0) ||
						(x == 5 && y == 0) ||
						(x == 7 && y == 1) ||
						(x == 6 && y == 1) ||
						(x == 7 && y == 2) ||

						(x == 2 && y == 3) ||//eyes
						(x == 5 && y == 3) ||

						(x == 0 && y == 5) ||//left arm side
						(x == 0 && y == 7) ||

						(x == 7 && y == 5) ||//right arm side
						(x == 7 && y == 7) ||

						(x == 2 && y == 7) ||//space between arms
						(x == 3 && y == 7) ||
						(x == 4 && y == 7) ||
						(x == 5 && y == 7) ||
						(x == 1 && y == 6) ||
						(x == 2 && y == 6) ||
						(x == 3 && y == 6) ||
						(x == 4 && y == 6) ||
						(x == 5 && y == 6) ||
						(x == 6 && y == 6) ||
						(x == 2 && y == 5) ||
						(x == 5 && y == 5))
					{
					}
					else
						SetPixel(hdc, pos.x + x - 4, pos.y + y - 2, RGB(255, 255, 255));
				}
			}
		}
		break;
	}
	state++;
}

IntVector2 Alien::GetPos()
{
	return pos;
}

RECT* Alien::GetRect()
{
	return rect;
}

int Alien::GetPoints()
{
	return points;
}