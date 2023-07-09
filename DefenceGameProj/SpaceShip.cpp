#include "SpaceShip.h"

SpaceShip::SpaceShip(POINT* p)
	:speed(10), shootPos(p[2])
{
	for (int i = 0; i < 7; i++)
		points[i] = p[i];
	shootPos = { p[2].x, p[2].y - 10 };
	SetCollider();
	color = RGB(255, 255, 255);
}

void SpaceShip::Draw(HDC hdc)
{
	HBRUSH hBrush, oldBrush;
	hBrush = CreateSolidBrush(color);
	oldBrush = (HBRUSH)SelectObject(hdc, hBrush);

	Polygon(hdc, points, 7);

	SelectObject(hdc, hBrush);
	DeleteObject(hBrush);
}

void SpaceShip::Update(int handle)
{
	for (int i = 0; i < 7; i++)
	{
		points[i].x += speed * handle;
	}
	shootPos.x += speed * handle;
	center.x += speed * handle;
	//printf("center : %d,%d\n", center.x, center.y);
}

void SpaceShip::SetCollider()
{
	center = { points[2].x, points[5].y+(points[5].y - points[4].y) / 2 };
	
	radius = (points[5].x - points[6].x)/2;
}
