#pragma once
#include "framework.h"
class Enemy
{
private:
	COLORREF color;
	POINT center;
	LONG radius;
	Vector2D force;
	BOOL canShoot;
	POINT shootPos;

	HBRUSH hBrush;
public:
	Enemy(const POINT& center, const COLORREF& ref);
	~Enemy() { DeleteObject(hBrush); };
	POINT GetCenter() { return center; }
	LONG GetRadius() { return radius; }
	POINT GetShootPos() { return shootPos; }
	BOOL GetCanShoot() { return canShoot; }
	void SetBrush();
	void SetCenter(const POINT& p) { center = p; }
	void SetRadius(const LONG& r) { radius = r; }
	void SetForce(const Vector2D& force);
	void SetCanShoot(BOOL s) { canShoot = s; }
	void SetShootPos(const POINT& p) { shootPos = p; }
	void Update();
	void Draw(HDC hdc);
};