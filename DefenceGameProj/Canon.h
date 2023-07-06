#pragma once
#include "GameObject.h"
class Canon : public GameObject
{
private:
	RECT Barrel;
	POINT ShootPos;
	Vector2D BarrelSlope;
	POINT BarrelPoint[4];
	LONG Dist[4];
	LONG ShootPosDist;

	FLOAT Angle;
	
	void SetBarrelPoint();
	void SetDist();
public:
	Canon();
	Canon(const POINT& center, const RECT& barrelPos);
	//오버라이드 메서드
	void Update(int handle)override;
	void Draw(HDC hdc)override;
	
	void Rotate(const FLOAT& theta);
};