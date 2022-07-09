#pragma once
#include "ZoteCommon.h"
#include "EnemyController.h"

using namespace Zote;

class GameManager : public Script
{
public:
	float spawnXRange = 5;
	float spawnY = 7;
	float spawnRate = 0.8f;
	Scene* scene = nullptr;

	void Update(float deltaTime) override;
	void CreateEnemy(vec2 spawn);
	void OnEnemyCollision(EnemyCollisionArgs args);

private:
	float time = 0;
};
