#include "Enemy.h"

Enemy::Enemy()
	:GameObject()
{
}

Enemy::Enemy(const POINT& center)
	:GameObject(center)
{
	Force = Vector2D(0, 5);
	Health = 3;
}

void Enemy::Update()
{
	Center.x += Force.getX();
	Center.y += Force.getY();
}
