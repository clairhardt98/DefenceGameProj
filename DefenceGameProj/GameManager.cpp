#include "GameManager.h"



GameManager::GameManager()
{
}

GameManager::GameManager(int startTime)
{
	CurTime = StartTime = startTime;
	FrameRate = 16;
}

void GameManager::InitGameObjects(const RECT& rectView)
{
	POINT CanonPos = { (rectView.right - rectView.left) / 2,rectView.bottom };
	RECT BarrelPos = { CanonPos.x - 10,CanonPos.y - 100,CanonPos.x + 10,CanonPos.y - 20 };
	GameObject* canon = new Canon(CanonPos, BarrelPos);
	Objects.push_back(canon);
}

void GameManager::UpdateGameObjects(int handle)
{
	if (CurTime - StartTime >= FrameRate)
		return;

	for (int i = 0; i < Objects.size(); i++)
	{
		Objects[i]->Update(handle);
	}
}

void GameManager::DeleteGameObjects()
{
	for (int i = 0; i < Objects.size(); i++)
	{
		if (Objects[i] != nullptr)
		{
			delete Objects[i];
			Objects[i] = nullptr;
		}
	}
}
