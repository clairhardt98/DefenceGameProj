#include "Bullet.h"

Bullet::Bullet()
	:GameObject()
{
	Force = 0;
	Direction = Vector2D(0, 0);
	Radius = 0;
}

Bullet::Bullet(const POINT& center, const LONG& force, const Vector2D& direction)
	:GameObject(center)
{
	Force = force;
	Direction = direction;
	Radius = 10;
	SetBullet();
}

void Bullet::Update()
{
	Center.x += Direction.getX();
	Center.y += Direction.getY();
}

void Bullet::Draw(HDC hdc)
{
	Ellipse(hdc, Center.x - Radius, Center.y - Radius, Center.x + Radius, Center.y + Radius);
}

void Bullet::SetBullet()
{
	Direction = Direction.normalize();
	Direction = Force * Direction ;
}

BOOL Bullet::IsColliding(GameObject* go)
{
	return 0;
}

void Bullet::Collision(GameObject* go)
{
}
