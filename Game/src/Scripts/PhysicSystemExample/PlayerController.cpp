#include "PlayerController.h"

void PlayerController::Start()
{
	thisEntity = GetEntity();
	thisEntity.AddComponent<SpriteComponent>().color = color;
	auto& transform = thisEntity.GetComponent<TransformComponent>();
	transform.SetPosition(startPos);
	transform.SetScale(startScale);
	thisEntity.AddComponent<PBody2DComponent>();
}

void PlayerController::Update(float deltaTime)
{
	CalculateMoveInput();
	CalculateMovement(deltaTime);
	CalculateShootInput();
}

void PlayerController::Shot()
{
	Entity bullet = scene->CreateEntity("Bullet Entity", "Bullet");
	
	//Transform
	auto& transform = thisEntity.GetComponent<TransformComponent>();
	auto& bulletTransform = bullet.GetComponent<TransformComponent>();
	bulletTransform.SetPosition(transform.GetPosition() + VEC3_UP * bulletOffset);
	bulletTransform.SetScale(bulletScale);
	
	//Visuals
	bullet.AddComponent<SpriteComponent>().color = bulletColor;

	//Physics
	auto& body = bullet.AddComponent<PBody2DComponent>();
	body.SetGScale(0);
	body.SetMode(PBody2DComponent::Mode::dynamic);
	body.ApplyLinearImpulse(bulletImpulse);
}

void PlayerController::CalculateShootInput()
{
	bool shootInput = Input::GetKeyPressed(ZOTE_KEY_SPACE);
	if (shootInput && !fire)
	{
		fire = true;
		Shot();
	}
	else if (!shootInput && fire)
	{
		fire = false;
	}	
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
}
