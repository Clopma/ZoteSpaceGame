#pragma once

#include <ZoteCommon.h>
using namespace Zote;

class ShipController : public Script {


public:
	void Update(float deltaTime) override;
	void OnCollision(Entity entity) override;
	void CalculateInputs();
	Scene* escena = nullptr;
	bool fin = false;
	vec2 moveInputs = {0, 0};
	float moveImpulse = 0.015f;
	float maxVelocity = 2.0f;
};
