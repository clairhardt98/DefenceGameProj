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
	//�Է¹��� handle�� ���� ����/������ ȸ��
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
	//���� 4�� rotate
	for (int i = 0; i < 4; i++)
	{
		BarrelPoint[i].x = Center.x + (Dist[i] * sin(theta));
		BarrelPoint[i].y = Center.y + (Dist[i] * cos(theta));
	}
	//�߻����� rotate
	ShootPos.x = Center.x + ShootPosDist * sin(theta);
	ShootPos.y = Center.y + ShootPosDist * cos(theta);
	//���� rotate
	BarrelSlope.setX(ShootPosDist * sin(theta));
	BarrelSlope.setY(ShootPosDist * cos(theta));
}

void Canon::SetBarrelPoint()
{
	//���� 4���� ��ġ
	BarrelPoint[0] = { Barrel.left,Barrel.top };
	BarrelPoint[1] = { Barrel.right,Barrel.top };
	BarrelPoint[2] = { Barrel.right,Barrel.bottom };
	BarrelPoint[3] = { Barrel.left,Barrel.bottom };
	//�߻������� ��ġ
	ShootPos = { Center.x, Center.y + Barrel.bottom - Barrel.top };
}

void Canon::SetDist()
{
	//������ ������ �� 4�������� �Ÿ�
	for (int i = 0; i < 4; i++)
	{
		Dist[i] = sqrt(pow(Center.x - BarrelPoint[i].x, 2) + pow(Center.y - BarrelPoint[i].y, 2));
	}
	//������ ����
	ShootPosDist = Barrel.bottom - Barrel.top;
}

