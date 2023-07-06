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

	
	void SetBarrelPoint();
	void SetDist();
public:
	Canon();
	Canon(const POINT& center, const RECT& barrelPos, const POINT& shootPos, const Vector2D& barrelSlope);
	//�������̵� �޼���
	void Update()override;
	void Draw()override;
	
	void Rotate(const FLOAT& theta);
};