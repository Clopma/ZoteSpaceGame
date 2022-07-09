#pragma once

#include "ZoteCommon.h"

using namespace Zote;

struct EnemyCollisionArgs 
{
	Entity enemyInstance;
	bool playerCollision = false;
	bool groundCollision = false;
	bool bulletCollision = false;
};

class EnemyController : public Script
{
public:
	Event<EnemyCollisionArgs> OnCollisionEvent;
	vec3 startScale = VEC3_ONE * .5f;
	vec2 impulse = -VEC2_UP * 1.f;
	
	str groundTag = "Ground";
	str playerTag = "Player";
	str bulletTag = "Bullet";

	void Start() override;
	void OnCollision(Entity entity) override;

private:
	Entity thisEntity;
};
