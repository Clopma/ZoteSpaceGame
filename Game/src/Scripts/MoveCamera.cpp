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

	//LOG("CameraPosition: " << transform->position.x << ", " << transform->position.y << ", " << transform->position.z);
}

void MoveCamera::LocateCamera(float deltaTime)
{
	vec3 moveDir = {0, 0, 0};

	if (Input::GetKeyPressed(ZOTE_KEY_W))
			transform->position += camera->front * cameraMoveSpeed * deltaTime;

	if (Input::GetKeyPressed(ZOTE_KEY_S))
		transform->position += -camera->front * cameraMoveSpeed * deltaTime;

	if (Input::GetKeyPressed(ZOTE_KEY_D))
		transform->position += camera->right * cameraMoveSpeed * deltaTime;

	if (Input::GetKeyPressed(ZOTE_KEY_A))
		transform->position += -camera->right * cameraMoveSpeed * deltaTime;
}

void MoveCamera::RotateCamera(float deltaTime)
{
	mouseDelta = lastMousePos - Input::GetMousePosition();
	lastMousePos = Input::GetMousePosition();

	transform->rotation.y += mouseDelta.x * -cameraTurnSpeed * deltaTime;
	transform->rotation.x += mouseDelta.y * cameraTurnSpeed * deltaTime;

	transform->rotation.x = std::clamp(transform->rotation.x, minPitchAngle, maxPitchAngle);
}
