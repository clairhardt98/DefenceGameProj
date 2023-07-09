#include "Bullet.h"



Bullet::Bullet(const POINT& center, const LONG& force, const Vector2D& direction)
{
	this->center = center;
	this->force = force;
	this->direction = direction;
	radius = 5;
}

void Bullet::Update()
{
	center.x += direction.getX();
	center.y += direction.getY();
}

void Bullet::Draw(HDC hdc)
{
	HBRUSH hBrush, oldBrush;
	hBrush = CreateSolidBrush(RGB(255,255,255));
	oldBrush = (HBRUSH)SelectObject(hdc, hBrush);

	Ellipse(hdc, center.x - radius, center.y - radius, center.x + radius, center.y + radius);

	SelectObject(hdc, hBrush);
	DeleteObject(hBrush);
	
}



BOOL Bullet::IsColliding()
{
	return 0;
}

void Bullet::Collision()
{
}
