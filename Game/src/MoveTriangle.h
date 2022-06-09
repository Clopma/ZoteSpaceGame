#pragma once
#include "ZoteCommon.h"

using namespace Zote;

class MoveTriangleScript : public Script
{
	float speed = 0.5f;
	TransformComponent* transform;

	virtual void Start() override;
	virtual void Update(float deltaTime) override;
};
