#include "PlayerController.h"

void PlayerController::Start()
{
	thisEntity = GetEntity();
}

void PlayerController::Update(float deltaTime)
{
	CalculateMoveInput();
	CalculateMovement(deltaTime);
}

void PlayerController::OnCollision(Entity other)
{
	auto& otherTag = other.GetComponent<TagComponent>();
	if (!otherTag.CompareTag("Enemy")) return;
	LOG("Destroyed: " << otherTag.name);
	scene->DestroyEntity(other);
}

void PlayerController::CalculateMoveInput()
{
	if (Input::GetKeyPressed(ZOTE_KEY_D))
		moveInput = -1;
	else if (Input::GetKeyPressed(ZOTE_KEY_A))
		moveInput = 1;
	else
		moveInput = 0;
}

void PlayerController::CalculateMovement(float deltaTime)
{
	if (moveInput == 0) return;
	//Movement
	auto& transform = thisEntity.GetComponent<TransformComponent>();
	vec3 newPosition = transform.GetPosition();
	newPosition.x += moveInput * speed * deltaTime;
	transform.SetPosition(newPosition);
	LOG(transform.GetPosition().x);
}
