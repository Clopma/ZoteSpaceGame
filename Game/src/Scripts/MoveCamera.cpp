#include "MoveCamera.h"

void MoveCamera::Start()
{
	transform = &GetEntity()->GetComponent<TransformComponent>();
	camera = &GetEntity()->GetComponent<CameraComponent>();
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

	if (Input::GetKeyPressed(ZOTE_KEY_A))
		moveDir.x = -1;
	else if (Input::GetKeyPressed(ZOTE_KEY_D))
		moveDir.x = 1;

	if (Input::GetKeyPressed(ZOTE_KEY_S))
		moveDir.z = 1;
	else if (Input::GetKeyPressed(ZOTE_KEY_W))
		moveDir.z = -1;

	transform->position += moveDir * cameraMoveSpeed * deltaTime;
}

void MoveCamera::RotateCamera(float deltaTime)
{
	mouseDelta = lastMousePos - Input::GetMousePosition();
	lastMousePos = Input::GetMousePosition();

	camera->yaw += mouseDelta.x * -cameraTurnSpeed * deltaTime;
	camera->pitch += mouseDelta.y * cameraTurnSpeed * deltaTime;

	camera->pitch = std::clamp(camera->pitch, minPitchAngle, maxPitchAngle);
}
