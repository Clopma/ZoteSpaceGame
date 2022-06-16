#pragma once
#include "ZoteCommon.h"

using namespace Zote;

class MoveCamera : public Script
{
	TransformComponent* transform = nullptr;

	vec2 mouseDelta = {0, 0};
	vec2 lastMousePos = {0, 0};

	float cameraTurnSpeed = 0.1f;
	float cameraMoveSpeed = 1;

	float maxPitchAngle = 89.0f;
	float minPitchAngle = -89.0f;

	virtual void Start() override;

	virtual void Update(float deltaTime) override;

	void LocateCamera(float deltaTime);
	void RotateCamera(float deltaTime);
};

