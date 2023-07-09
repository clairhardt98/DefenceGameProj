#pragma once
#include "framework.h"

class SpaceShip
{
private:
	COLORREF color;

	POINT points[7];
	LONG speed;//움직임은 x값을 더하거나 빼주기만 하면 그만임
	POINT shootPos;
	//콜라이더
	POINT center;
	LONG radius;
public:
	SpaceShip(POINT* p);
		
	void Draw(HDC hdc);
	void Update(int handle);
	void SetCollider();
	void SetColor(const COLORREF& ref) { color = ref; }
	POINT GetCenter() { return center; }
	LONG GetRadius() { return radius; }
	
	POINT getShootPos() { return shootPos; }

};