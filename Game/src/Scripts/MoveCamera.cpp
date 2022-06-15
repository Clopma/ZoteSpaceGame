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

	vec3 newPosition = transform->GetPosition();

	if (Input::GetKeyPressed(ZOTE_KEY_W))
		newPosition += transform->GetForward() * cameraMoveSpeed * deltaTime;

	if (Input::GetKeyPressed(ZOTE_KEY_S))
		newPosition += -transform->GetForward() * cameraMoveSpeed * deltaTime;

	if (Input::GetKeyPressed(ZOTE_KEY_D))
		newPosition += transform->GetRight() * cameraMoveSpeed * deltaTime;

	if (Input::GetKeyPressed(ZOTE_KEY_A))
		newPosition += -transform->GetRight() * cameraMoveSpeed * deltaTime;

	transform->SetPosition(newPosition);
}

void MoveCamera::RotateCamera(float deltaTime)
{
	mouseDelta = lastMousePos - Input::GetMousePosition();
	lastMousePos = Input::GetMousePosition();

	vec3 newRotation = transform->GetRotation();

	newRotation.y += mouseDelta.x * cameraTurnSpeed * deltaTime;
	newRotation.x += mouseDelta.y * -cameraTurnSpeed * deltaTime;

	newRotation.x = std::clamp(newRotation.x, minPitchAngle, maxPitchAngle);

	transform->SetRotation(newRotation);
}
