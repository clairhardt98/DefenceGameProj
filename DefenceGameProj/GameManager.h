#pragma once
#include "GameObject.h"
#include "Canon.h"
#include "Bullet.h"
#include <vector>

//��ü�� ���� ����
std::vector<GameObject*> Objects;

void InitGameObjects(std::vector<GameObject*>& Objects);
void UpdateGameObjects(std::vector<GameObject*>& Objects);