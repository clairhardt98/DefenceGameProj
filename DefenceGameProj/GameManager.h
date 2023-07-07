#pragma once
#include <vector>
#include <Windows.h>
#include "GameObject.h"
#include "Canon.h"
#include "Bullet.h"


class GameManager
{
private:
	std::vector<GameObject*> Objects;
	
public:
	GameManager();
	
	std::vector<GameObject*>& GetGameObjects() { return Objects; }
	void InitGameObjects(const RECT& rectView);
	void UpdateGameObjects();
	void DrawGameObjects(HDC hdc);
	void DeleteGameObjects();
	void InstantiateBullet(Canon& canon);
};
//객체들 담을 변수
