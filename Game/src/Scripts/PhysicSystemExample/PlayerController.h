#pragma once
#include "ZoteCommon.h"

using namespace Zote;

class PlayerController : public Script
{
public:

	float speed = 10;
	int moveInput = 0;
	Scene* scene = nullptr;

	void Start() override;
	void Update(float deltaTime) override;
	void OnCollision(Entity* other) override;

private:

	Entity* thisEntity = nullptr;
	void CalculateMoveInput();
	void CalculateMovement(float deltaTime);
};
