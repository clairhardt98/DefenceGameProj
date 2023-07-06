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
	int StartTime;
	int CurTime;
	int FrameRate;
public:
	GameManager();
	GameManager(int StartTime);

	void SetCurTime(int Time) { CurTime = Time; };

	void InitGameObjects(const RECT& rectView);
	void UpdateGameObjects(int handle);
	void DeleteGameObjects();
};
//객체들 담을 변수
