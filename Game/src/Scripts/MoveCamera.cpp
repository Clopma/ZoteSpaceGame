#include "MoveCamera.h"

void MoveCamera::Start()
{
	transform = &GetEntity()->GetComponent<TransformComponent>();
	lastMousePos = Input::GetMousePosition();
}

void MoveCamera::Update(float deltaTime)
{
	LocateCamera(deltaTime);
	RotateCamera(deltaTime);
}

void MoveCamera::LocateCamera(float deltaTime)
{
	vec3 moveDir = {0, 0, 0};

	if (Input::GetKeyPressed(ZOTE_KEY_W))
			transform->position += transform->GetForward() * cameraMoveSpeed * deltaTime;

	if (Input::GetKeyPressed(ZOTE_KEY_S))
		transform->position += -transform->GetForward() * cameraMoveSpeed * deltaTime;

	if (Input::GetKeyPressed(ZOTE_KEY_D))
		transform->position += transform->GetRight() * cameraMoveSpeed * deltaTime;

	if (Input::GetKeyPressed(ZOTE_KEY_A))
		transform->position += -transform->GetRight() * cameraMoveSpeed * deltaTime;
}

void MoveCamera::RotateCamera(float deltaTime)
{
	mouseDelta = lastMousePos - Input::GetMousePosition();
	lastMousePos = Input::GetMousePosition();

	transform->rotation.y += mouseDelta.x * cameraTurnSpeed * deltaTime;
	transform->rotation.x += mouseDelta.y * -cameraTurnSpeed * deltaTime;

	transform->rotation.x = std::clamp(transform->rotation.x, minPitchAngle, maxPitchAngle);
}
