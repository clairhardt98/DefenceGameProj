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
	int CurrTime;
	
	//Enemy 배열 다루기 위한 변수
	Vector2D EnemyMovement;
	int EnemyMoveState;
	int MoveCnt;
	//gunny에 대한 정보
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
};
//객체들 담을 변수
