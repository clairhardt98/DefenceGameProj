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

	//��������� �̷�� ����
	FLOAT Angle;
	BOOL OnLeft;
	
	void SetBarrelPoint();
	void SetDist();
public:
	Canon();
	Canon(const POINT& center, const RECT& barrelPos);
	//�������̵� �޼���
	void Update()override;
	void Draw(HDC hdc)override;
	
	void SetAngle();
	void SetSlope(Vector2D& v);
	void Rotate(const FLOAT& theta);
	POINT GetShootPos() { return ShootPos; };
	Vector2D& GetSlope() { return BarrelSlope; };
};