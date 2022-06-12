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
	float dirZ = 0;

	if (Input::GetKeyPressed(ZOTE_KEY_J))
		dirX = -1;
	else if (Input::GetKeyPressed(ZOTE_KEY_L))
		dirX = 1;

	if (Input::GetKeyPressed(ZOTE_KEY_K))
		dirZ = -1;
	else if (Input::GetKeyPressed(ZOTE_KEY_I))
		dirZ = 1;

	transform->position.x += dirX * speed * deltaTime;
	transform->position.z += dirZ * speed * deltaTime;
}