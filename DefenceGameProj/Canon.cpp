#include "Canon.h"


Canon::Canon()
	:GameObject()
{
	Barrel = { 0,0,0,0 };
	ShootPos = { 0,0 };
	BarrelSlope = Vector2D(0, 0);
	SetBarrelPoint();
	SetDist();
	Angle = 0;
}

Canon::Canon(const POINT& center, const RECT& barrelPos)
	:GameObject(center)
{
	Barrel = barrelPos;
	SetBarrelPoint();
	SetDist();
	BarrelSlope = Vector2D(0, ShootPos.y);
}

void Canon::Update(int handle)
{
	//입력받은 handle에 따라 왼쪽/오른쪽 회전
	if ((!handle && Angle > 0) || (handle && Angle < 0))
	{
		Angle *= -1;
	}

	Rotate(Angle);
}
void Canon::Draw(HDC hdc)
{
	Polygon(hdc, BarrelPoint, 4);
}
void Canon::Rotate(const FLOAT& theta)
{
	//포신 4개 rotate
	for (int i = 0; i < 4; i++)
	{
		BarrelPoint[i].x = Center.x + (Dist[i] * sin(theta));
		BarrelPoint[i].y = Center.y + (Dist[i] * cos(theta));
	}
	//발사지점 rotate
	ShootPos.x = Center.x + ShootPosDist * sin(theta);
	ShootPos.y = Center.y + ShootPosDist * cos(theta);
	//기울기 rotate
	BarrelSlope.setX(ShootPosDist * sin(theta));
	BarrelSlope.setY(ShootPosDist * cos(theta));
}

void Canon::SetBarrelPoint()
{
	//포신 4점의 위치
	BarrelPoint[0] = { Barrel.left,Barrel.top };
	BarrelPoint[1] = { Barrel.right,Barrel.top };
	BarrelPoint[2] = { Barrel.right,Barrel.bottom };
	BarrelPoint[3] = { Barrel.left,Barrel.bottom };
	//발사지점의 위치
	ShootPos = { Center.x, Center.y + Barrel.bottom - Barrel.top };
}

void Canon::SetDist()
{
	//원점과 포신의 각 4점사이의 거리
	for (int i = 0; i < 4; i++)
	{
		Dist[i] = sqrt(pow(Center.x - BarrelPoint[i].x, 2) + pow(Center.y - BarrelPoint[i].y, 2));
	}
	//포신의 길이
	ShootPosDist = Barrel.bottom - Barrel.top;
}

