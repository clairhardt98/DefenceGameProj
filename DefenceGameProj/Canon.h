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

	//수직방향과 이루는 각도
	FLOAT Angle;
	BOOL OnLeft;
	
	void SetBarrelPoint();
	void SetDist();
public:
	Canon();
	Canon(const POINT& center, const RECT& barrelPos);
	//오버라이드 메서드
	void Update()override;
	void Draw(HDC hdc)override;
	
	void SetAngle();
	void SetSlope(Vector2D& v);
	void Rotate(const FLOAT& theta);
	POINT GetShootPos() { return ShootPos; };
	Vector2D& GetSlope() { return BarrelSlope; };
};