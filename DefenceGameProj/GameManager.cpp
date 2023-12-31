#include "GameManager.h"

GameManager::GameManager(POINT* P)
	:ss(P)
{
	PlayerHP = 3;
	ss.SetColor(RGB(0, 255, 0));
	Score = 0;
	KillCnt = 0;
	GameOver = GameClear = false;
}
void GameManager::InitGameObjects(const RECT& rectView)
{
	
	EraseCoolTick = InitTime = CurrTime = EnemyMoveTick = ShootCoolTick = GetTickCount();
	const int startX = 50;
	const int startY = 50;
	const int interval = (rectView.right - rectView.left - 100) / 10;

	int MoveCnt = 0;
	int cnt = 6;
	EnemyMovement = Vector2D(1, 0);
	EnemyMoveState = 0;
	for (int i = 0; i < 50; i++)
	{
		COLORREF color;
		if (i % 10 == 0)cnt--;
		POINT temp = { startX + (i % 10) * interval, startY * cnt };
		//색상 지정
		if (i < 10) color = RGB(255, 0, 0);
		else if (i < 20) color = RGB(255, 127, 0);
		else if (i < 30) color = RGB(255, 255, 0);
		else if (i < 40)color = RGB(0, 255, 0);
		else color = RGB(0, 0, 255);

		Enemy* e = new Enemy(temp,color);
		
		if (i < 10) e->SetCanShoot(TRUE);
		enemies.push_back(e);
	}
	//여기서 적 배열, gunny 배열 생성 및 할당
	//여기서 시작한 시간 측정
}
void GameManager::UpdateGameObjects(int handle)
{
	CurrTime = GetTickCount();

	ss.Update(handle);
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->Update();
	}
	//적들이 움직이는 것은 쿨타임을 줌
	if (CurrTime - EnemyMoveTick > 100 - KillCnt * 2)
	{
		MoveCnt++;
		for (int i = 0; i < enemies.size(); i++)
		{
			enemies[i]->Update();
			if(enemies[i]->GetCanShoot())
				RandomEnemyInstantiateBullet(i);
		}

		EnemyMoveTick = CurrTime;
	}
	//50번 움직였으면 움직임 변경
	if (MoveCnt > 50)
	{
		printf("changed move state, in %d\n", EnemyMoveState);
		MoveCnt = 0;
		ChangeEnemyDirection();
	}
	//충돌로직
	CollisionLoop();
	//충돌돼서 사라진 애들 다 지우기
	//EraseObjects();
}
void GameManager::ChangeEnemyDirection()
{
	EnemyMoveState += 1;
	if (EnemyMoveState == 4)
		EnemyMoveState = 0;
	switch (EnemyMoveState)
	{
	case 0:
		EnemyMovement = Vector2D(1, 0);
		break;
	case 1:
		EnemyMovement = Vector2D(0, 1);
		break;
	case 2:
		EnemyMovement = Vector2D(-1, 0);
		break;
	case 3:
		EnemyMovement = Vector2D(0, 1);
		break;
	}
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->SetForce(EnemyMovement);
	}

}
void GameManager::DrawGameObjects(HDC hdc)
{
	ss.Draw(hdc);
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->Draw(hdc);
	}

	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->Draw(hdc);
	}
}
void GameManager::DeleteGameObjects()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i] != nullptr)
		{
			delete bullets[i];
			bullets[i] = nullptr;
		}
	}

	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

}
void GameManager::InstantiateBullet(BOOL tag)
{
	CurrTime = GetTickCount();
	if (CurrTime - ShootCoolTick > 400)
	{
		Bullet* b = new Bullet(ss.getShootPos(), 10, Vector2D(0, -20));
		b->SetTag(tag);//누가 쐈는지에 대한 태그
		printf("ShootPos x : %d\n", (int)ss.getShootPos().x);
		bullets.push_back(b);
		ShootCoolTick = CurrTime;
	}

}
void GameManager::InstantiateBullet(BOOL tag, int idx)
{
	CurrTime = GetTickCount();
	if (CurrTime - EnemyShootCoolTick > 500)
	{
		Bullet* b = new Bullet(enemies[idx]->GetShootPos(), 10, Vector2D(0, 20));
		b->SetTag(tag);//누가 쐈는지에 대한 태그
		bullets.push_back(b);
		EnemyShootCoolTick = CurrTime;
	}

}
void GameManager::CollisionLoop()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		//내가 발사한 bullet에 대한 로직
		if (!bullets[i]->GetTag())
		{
			for (int j = 0; j < enemies.size(); j++)
			{
				if (BulletCollision(bullets[i], enemies[j]))
				{
					if (j + 10 < 50 && enemies[j]->GetCanShoot())
					{
						enemies[j]->SetCanShoot(FALSE);
						enemies[j + 10]->SetCanShoot(TRUE);
						printf("enemy %d hit, new shooter enemy is enemy %d\n", j, j + 10);

					}
				}
			}
			for (int j = 0; j < bullets.size(); j++)
			{
				if (i == j || !bullets[j]->GetTag()) continue;
				BulletCollision(bullets[i], bullets[j]);
			}
		}
		//적이 발사한 bullet에 대한 로직
		else
		{
			if (BulletCollision(bullets[i], &ss))
			{
				printf("player hit!\n");
				PlayerHP--;
				if (PlayerHP <= 0)GameOver = TRUE;
				COLORREF color;
				switch (PlayerHP)
				{
				case 2:
					color = RGB(255, 255, 0);
					break;
				case 1:
					color = RGB(255, 0, 0);
					break;
				default:
					color = RGB(0, 255, 0);
					break;
				}
				ss.SetColor(color);
			}
			for (int j = 0; j < bullets.size(); j++)
			{
				if (i == j || bullets[j]->GetTag()) continue;
				BulletCollision(bullets[i], bullets[j]);
			}
		}
	}
}
BOOL GameManager::BulletCollision(Bullet* bullet, Enemy* enemy)
{
	FLOAT dist = sqrt(pow(bullet->GetCenter().x - enemy->GetCenter().x, 2)
		+ pow(bullet->GetCenter().y - enemy->GetCenter().y, 2));
	if (bullet->GetRadius() + enemy->GetRadius() > dist)
	{
		bullet->SetCenter({ 2000,2000 });
		bullet->SetRadius(0);
		enemy->SetCenter({ -2000,-2000 });
		enemy->SetShootPos({ -2000,-2000});
		enemy->SetRadius(0);
		Score += 100;
		KillCnt++;
		if (KillCnt == 50)GameClear = TRUE;
		printf("Score : %d\n", Score);
		return TRUE;
		//맞으면 멀리 보내버리기
	}
	else return false;

}
BOOL GameManager::BulletCollision(Bullet* bullet, SpaceShip* ss)
{
	FLOAT dist = sqrt(pow(bullet->GetCenter().x - ss->GetCenter().x, 2)
		+ pow(bullet->GetCenter().y - ss->GetCenter().y, 2));
	if (bullet->GetRadius() + ss->GetRadius() > dist)
	{
		bullet->SetCenter({ 2000,2000 });
		bullet->SetRadius(0);

		return TRUE;
		//맞으면 멀리 보내버리기
	}
	return false;
}
BOOL GameManager::BulletCollision(Bullet* bullet1, Bullet* bullet2)
{
	FLOAT dist = sqrt(pow(bullet1->GetCenter().x - bullet2->GetCenter().x, 2)
		+ pow(bullet1->GetCenter().y - bullet2->GetCenter().y, 2));
	if (bullet1->GetRadius() + bullet2->GetRadius() > dist)
	{
		bullet1->SetCenter({ 2000,2000 });
		bullet1->SetRadius(0);
		bullet2->SetCenter({ 2000,2000 });
		bullet2->SetRadius(0);
		Score += 500;
		return TRUE;
		//맞으면 멀리 보내버리기
	}
	return false;
}
void GameManager::RandomEnemyInstantiateBullet(int idx)
{
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, 9);
	int rand = dis(gen);

	if (idx % 10 == rand)
	{
		InstantiateBullet(true, idx);
	}
}
void GameManager::EraseObjects()
{
	CurrTime = GetTickCount();
	if(CurrTime - EraseCoolTick >1000)
	{
		enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](Enemy* obj) {return obj->GetCenter().x <-1000; }), enemies.end());
		bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](Bullet* obj) {return obj->GetCenter().y > 1000; }), bullets.end());
		printf("bullets and enemies erased\n");
		EraseCoolTick = CurrTime;
	}
}