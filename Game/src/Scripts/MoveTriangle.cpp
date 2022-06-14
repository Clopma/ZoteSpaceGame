#include "MoveTriangle.h"


void MoveTriangleScript::Start()
{
	printf("Started Triangle");
	transform = &GetEntity()->GetComponent<TransformComponent>();
	//transform = &GetEntity()->GetTransform();
}

void MoveTriangleScript::Update(float deltaTime)
{
	float dirX = 0;

	if (Input::GetKeyPressed(ZOTE_KEY_J))
		dirX = -1;
	else if (Input::GetKeyPressed(ZOTE_KEY_L))
		dirX = 1;

	if (Input::GetKeyPressed(ZOTE_KEY_I))
		transform->position += -transform->GetForward() * 0.5f * deltaTime;

	transform->rotation.y += dirX * speed * deltaTime;
	//LOG(transform->position.x << ", " << transform->position.y << ", " << transform->position.z)
}