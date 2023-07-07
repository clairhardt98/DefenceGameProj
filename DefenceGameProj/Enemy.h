#pragma once
#include "GameObject.h"
class Enemy :public GameObject
{
private:
	LONG Radius;
	int Health;
	Vector2D Force;
public:
	Enemy();
	Enemy(const POINT& center);

	void Update()override;
	void Draw(HDC hdc)override;
};