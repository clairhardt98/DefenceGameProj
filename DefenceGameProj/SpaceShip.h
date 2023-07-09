#pragma once
#include "framework.h"

class SpaceShip
{
private:
	COLORREF color;

	POINT points[7];
	LONG speed;//�������� x���� ���ϰų� ���ֱ⸸ �ϸ� �׸���
	POINT shootPos;
	//�ݶ��̴�
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