#pragma once
#include "GameObject.h"

class Bullet :public GameObject
{
private:
	LONG Force;
	Vector2D Direction;
	LONG Radius;
public:
	Bullet();
	Bullet(const POINT& center, const LONG& force, const Vector2D& direction);

	void Update(int handle)override;
	void Draw(HDC hdc)override;

	BOOL IsColliding(GameObject* go);
	void Collision(GameObject* go);
};