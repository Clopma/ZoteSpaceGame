#pragma once
#include "ZoteCommon.h"

using namespace Zote;

class PlayerController : public Script
{
public:
	Color bulletColor = Color::red;
	vec3 bulletScale = VEC3_ONE * .25f;
	float bulletOffset = .8f;
	vec3 bulletImpulse = VEC3_UP * 3.f;

	Scene* scene = nullptr;
	Color color = Color::blue;
	vec3 startPos = { 0, -6.5f, 0 };
	vec3 startScale = { 3, 1, 1 };
	float speed = 10;
	int moveInput = 0;

	void Start() override;
	void Update(float deltaTime) override;
	void Shot();

private:
	bool fire = false;
	Entity thisEntity;
	void CalculateShootInput();
	void CalculateMoveInput();
	void CalculateMovement(float deltaTime);
};
