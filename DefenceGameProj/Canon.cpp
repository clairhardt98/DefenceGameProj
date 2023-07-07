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
	Angle = 0;
}

void Canon::Update()
{	
	SetAngle();
	Rotate(Angle);
}
void Canon::Draw(HDC hdc)
{
	Polygon(hdc, BarrelPoint, 4);
	Ellipse(hdc, Center.x - 50, Center.y - 30, Center.x + 50, Center.y + 30);
	Ellipse(hdc, ShootPos.x - 5, ShootPos.y - 5, ShootPos.x + 5, ShootPos.y + 5);
}
void Canon::SetAngle()
{
	Angle = acos(-BarrelSlope.getY() / BarrelSlope.getMag());
	
}
void Canon::SetSlope(Vector2D& v)
{
	BarrelSlope = Vector2D(-Center.x + v.getX(), -Center.y + v.getY());
	if(Center.x - v.getX()>0)
	{
		
		OnLeft = TRUE;
	}
	else
	{
		
		OnLeft = FALSE;
	}
}
void Canon::Rotate(const FLOAT& theta)
{
	FLOAT t = theta;
	if (OnLeft)
		t *= -1;
	
	//포신 4개 rotate
	for (int i = 0; i < 4; i++)
	{
		BarrelPoint[i].x = Center.x + (Dist[i] * sin(PI - t));
		BarrelPoint[i].y = Center.y + (Dist[i] * cos(PI - t));
	}
	//발사지점 rotate
	ShootPos.x = Center.x + ShootPosDist * sin(PI - t);
	ShootPos.y = Center.y + ShootPosDist * cos(PI - t);
	
}

void Canon::SetBarrelPoint()
{
	//포신 4점의 위치
	BarrelPoint[0] = { Barrel.left,Barrel.top };
	BarrelPoint[1] = { Barrel.right,Barrel.top };
	BarrelPoint[2] = { Barrel.right,Barrel.bottom };
	BarrelPoint[3] = { Barrel.left,Barrel.bottom };

	
	//발사지점의 위치
	//ShootPos = { Center.x, Center.y + Barrel.top - Barrel.bottom };
	
}

void Canon::SetDist()
{
	//원점과 포신의 각 4점사이의 거리
	for (int i = 0; i < 4; i++)
	{
		Dist[i] = sqrt(pow(Center.x - BarrelPoint[i].x, 2) + pow(Center.y - BarrelPoint[i].y, 2));
	}
	//포신의 길이
	ShootPosDist = Barrel.bottom - Barrel.top + 30;
}

