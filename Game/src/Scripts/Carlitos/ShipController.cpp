#include "ShipController.h"

#include "MeteoriteSpawner.h"


void ShipController::Update(float deltaTime)
{
	CalculateInputs();
	
	PBody2DComponent& body = GetEntity().GetComponent<PBody2DComponent>();
	TransformComponent& transform = GetEntity().GetComponent<TransformComponent>();

	body.SetAngularVelocity(0);
	transform.SetRotation(quat(0, 0, 1, 0));

	body.ApplyLinearImpulse(moveInputs * moveImpulse);
	auto velocity = body.GetLinearVelocity();

	float totalVelocity = abs(velocity.x) + abs(velocity.y);
	if (totalVelocity > maxVelocity)
	{
		float velx = maxVelocity * velocity.x / totalVelocity;
		float vely = maxVelocity * velocity.y / totalVelocity;
		body.SetLinearVelocity(vec2(velx, vely));
	}
}


void ShipController::OnCollision(Entity entity)
{
	if (!fin && entity.GetComponent<TagComponent>().CompareName("meteorito")) {
		fin = true;
		Entity cartel = escena->CreateEntity();
		TransformComponent& transform = cartel.GetComponent<TransformComponent>();
		transform.SetPosition(vec3(0, 0, 0));
		transform.SetScale(vec3(8.0f, 4.3f, 1.0f));
		cartel.AddComponent<SpriteComponent>("Textures/dead.png");
	}
}

void ShipController::CalculateInputs()
{
	moveInputs = {0, 0};

	if (Input::GetKeyPressed(ZOTE_KEY_W)) moveInputs.y += 1;
	if (Input::GetKeyPressed(ZOTE_KEY_S)) moveInputs.y -= 1;
	
	if (Input::GetKeyPressed(ZOTE_KEY_A)) moveInputs.x += 1;
	if (Input::GetKeyPressed(ZOTE_KEY_D)) moveInputs.x -= 1;
}


