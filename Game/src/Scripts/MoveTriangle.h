#pragma once
#include "ZoteCommon.h"

using namespace Zote;

class MoveTriangleScript : public Script
{
	TransformComponent* transform;

	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void OnCollision(Entity* rb) override;
};
