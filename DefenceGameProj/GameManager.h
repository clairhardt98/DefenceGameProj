#pragma once
#include "GameObject.h"
#include "Canon.h"
#include "Bullet.h"
#include <vector>

//객체들 담을 변수
std::vector<GameObject*> Objects;

void InitGameObjects(std::vector<GameObject*>& Objects);
void UpdateGameObjects(std::vector<GameObject*>& Objects);