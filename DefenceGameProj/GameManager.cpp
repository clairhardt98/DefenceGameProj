#include "GameManager.h"



GameManager::GameManager()
{
}



void GameManager::InitGameObjects(const RECT& rectView)
{
	
}

void GameManager::UpdateGameObjects()
{
	for (int i = 0; i < Objects.size(); i++)
	{
		Objects[i]->Update();
	}
	
}

void GameManager::DrawGameObjects(HDC hdc)
{
	for (int i = 0; i < Objects.size(); i++)
	{
		Objects[i]->Draw(hdc);
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

void GameManager::InstantiateBullet(Canon& canon)
{
	GameObject* obj = new Bullet(canon.GetShootPos(),5,canon.GetSlope());
	Objects.push_back(obj);
}
