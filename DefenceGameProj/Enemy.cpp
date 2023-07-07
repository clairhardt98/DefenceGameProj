#include "Enemy.h"

Enemy::Enemy()
	:GameObject()
{
}

Enemy::Enemy(const POINT& center)
	:GameObject(center)
{
	Force = Vector2D(0, 5);
	Radius = 10;
	Health = 3;
}

void Enemy::Update()
{
	Center.x += Force.getX();
	Center.y += Force.getY();
}

void Enemy::Draw(HDC hdc)
{
	Ellipse(hdc, Center.x - Radius, Center.y - Radius, Center.x + Radius, Center.y + Radius);
}
