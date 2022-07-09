#include "GameManager.h"

void GameManager::Update(float deltaTime)
{
	time += deltaTime;

	if (time < spawnRate) return;

	time = 0;
	float spawnX = RandomFloat(-spawnXRange, spawnXRange);
	CreateEnemy({ spawnX, spawnY });
}

void GameManager::CreateEnemy(vec2 spawn)
{
	auto enemyController = new EnemyController();
	auto dlg = new Delegate<EnemyCollisionArgs>(this, &GameManager::OnEnemyCollision);
	enemyController->OnCollisionEvent.AddListener(dlg);

	Entity enemy = scene->CreateScriptableEntity( enemyController, "Enemy Entity", "Enemy");
	auto& transform = enemy.GetComponent<TransformComponent>();
	transform.SetPosition({ spawn.x, spawn.y, 0 });
	//scene->DestroyEntity(enemy);
}

void GameManager::OnEnemyCollision(EnemyCollisionArgs args)
{
	if (args.bulletCollision)
	{
		scene->DestroyEntity(args.enemyInstance);
		return;
	}
	if (args.groundCollision || args.playerCollision)
	{
		scene->GetWindow()->close = true;
	}
}
