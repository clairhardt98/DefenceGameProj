#pragma once
#include <Windows.h>
#include "framework.h"
#include "SpaceShip.h"
#include "Bullet.h"
#include "Enemy.h"
#include <random>


class GameManager
{
private:
	int PlayerHP;
	int Score;
	int KillCnt;

	RECT rectView;
	SpaceShip ss;

	std::vector<Bullet*> bullets;
	std::vector<Enemy*> enemies;
	//std::vector<Gunny> gunnies;
	
	//랜덤 생성에 필요한 변수
	std::random_device rd;
	
	//쿨타임 로직에 필요한 변수들
	int InitTime;
	int EnemyMoveTick;
	int ShootCoolTick;
	int EnemyShootCoolTick;
	int EraseCoolTick;
	int CurrTime;
	
	//Enemy 배열 다루기 위한 변수
	Vector2D EnemyMovement;
	int EnemyMoveState;
	int MoveCnt;
	//게임 클리어/오버에 대한 정보
	BOOL GameOver;
	BOOL GameClear;
public:
	GameManager(POINT* P);
	
	void InitGameObjects(const RECT& rectView);
	void UpdateGameObjects(int handle);
	void ChangeEnemyDirection();
	void DrawGameObjects(HDC hdc);
	void DeleteGameObjects();
	void InstantiateBullet(BOOL tag);
	void InstantiateBullet(BOOL tag, int idx);
	void CollisionLoop();
	BOOL BulletCollision(Bullet* bullet, Enemy* enemy);
	BOOL BulletCollision(Bullet* bullet, SpaceShip* ss);
	BOOL BulletCollision(Bullet* bullet1, Bullet* bullet2);
	void RandomEnemyInstantiateBullet(int idx);
	void EraseObjects();
	BOOL GetGameOver() { return GameOver; }
	BOOL GetGameClear() { return GameClear; }
	

	int GetScore() { return Score; }
	int GetKillCnt() { return KillCnt; }
};
//객체들 담을 변수
