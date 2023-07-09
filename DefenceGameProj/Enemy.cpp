#include "Enemy.h"

Enemy::Enemy(const POINT& center, const COLORREF& ref)
	:radius(10)
{
	this->center = center;
	shootPos = { center.x, center.y + 7 };
	SetForce(Vector2D(1, 0));
	canShoot = false;
	color = ref;
}

void Enemy::SetForce(const Vector2D& force)
{
	this->force = force;
}

void Enemy::Update()
{
	center.x += force.getX();
	center.y += force.getY();
	shootPos.x += force.getX();
	shootPos.y += force.getY();
}

void Enemy::Draw(HDC hdc)
{
	HBRUSH hBrush, oldBrush;
	hBrush = CreateSolidBrush(color);
	oldBrush = (HBRUSH)SelectObject(hdc, hBrush);

	Ellipse(hdc, center.x - radius, center.y - radius, center.x + radius, center.y + radius);

	SelectObject(hdc, hBrush);
	DeleteObject(hBrush);
	
}
