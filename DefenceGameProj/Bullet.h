#pragma once
#include "framework.h"

class Bullet 
{
private:
	POINT center;
	LONG force;
	Vector2D direction;
	LONG radius;
	BOOL Tag;
public:
	Bullet(const POINT& center, const LONG& force, const Vector2D& direction);

	void Update();
	void Draw(HDC hdc);

	POINT GetCenter() { return center; }
	LONG GetRadius() { return radius; }
	void SetCenter(const POINT& p) { center = p; }
	void SetRadius(const LONG& r) { radius = r; }

	void SetTag(BOOL tag) { Tag = tag; };
	BOOL GetTag() { return Tag; }

	BOOL IsColliding();
	void Collision();
};