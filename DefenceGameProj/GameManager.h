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
	
	//���� ������ �ʿ��� ����
	std::random_device rd;
	
	//��Ÿ�� ������ �ʿ��� ������
	int InitTime;
	int EnemyMoveTick;
	int ShootCoolTick;
	int EnemyShootCoolTick;
	int CurrTime;
	
	//Enemy �迭 �ٷ�� ���� ����
	Vector2D EnemyMovement;
	int EnemyMoveState;
	int MoveCnt;
	//gunny�� ���� ����
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
//��ü�� ���� ����
