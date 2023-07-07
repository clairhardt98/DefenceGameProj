#pragma once
#include "framework.h"
#include "Vector2D.h"
#include <cmath>
const FLOAT PI = 3.141592;
class GameObject
{
protected:
	POINT Center;
public:
	GameObject() { Center = { 0,0 }; }
	GameObject(const POINT& center) { Center = center; }
	virtual void Update() = 0;
	virtual void Draw(HDC hdc) = 0;
};