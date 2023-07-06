#include "Canon.h"


Canon::Canon()
	:GameObject()
{
	Barrel = { 0,0,0,0 };
	ShootPos = { 0,0 };
	BarrelSlope = Vector2D(0, 0);
	SetBarrelPoint();
	SetDist();
}

Canon::Canon(const POINT& center, const RECT& barrelPos, const POINT& shootPos, const Vector2D& barrelSlope)
	:GameObject(center)
{
	Barrel = barrelPos;
	ShootPos = shootPos;
	BarrelSlope = barrelSlope;
	SetBarrelPoint();
	SetDist();
}

void Canon::Update()
{

}

void Canon::Draw()
{
}



void Canon::Rotate(const FLOAT& theta)
{
	for (int i = 0; i < 4; i++)
	{
		BarrelPoint[i].x = Center.x + (Dist[i] * sin(theta));
		BarrelPoint[i].y = Center.y + (Dist[i] * cos(theta));
	}
}

void Canon::SetBarrelPoint()
{
	BarrelPoint[0] = { Barrel.left,Barrel.top };
	BarrelPoint[1] = { Barrel.right,Barrel.top };
	BarrelPoint[2] = { Barrel.right,Barrel.bottom };
	BarrelPoint[3] = { Barrel.left,Barrel.bottom };
}

void Canon::SetDist()
{
	for (int i = 0; i < 4; i++)
	{
		Dist[i] = sqrt(pow(Center.x - BarrelPoint[i].x, 2) + pow(Center.y - BarrelPoint[i].y,2));
	}	
}

