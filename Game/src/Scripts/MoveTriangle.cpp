#include "MoveTriangle.h"


void MoveTriangleScript::Start()
{
	printf("Started Triangle");
	transform = &GetEntity()->GetComponent<TransformComponent>();
}

void MoveTriangleScript::Update(float deltaTime)
{
	float dirX = 0;

	if (Input::GetKeyPressed(ZOTE_KEY_J))
		transform->rotation -= vec3(0, 1, 0) * 40.0f * deltaTime;
	else if (Input::GetKeyPressed(ZOTE_KEY_L))
		transform->rotation += vec3(0, 1, 0) * 40.0f * deltaTime;

	if (Input::GetKeyPressed(ZOTE_KEY_I))
		transform->position += transform->GetForward() * 1.0f * deltaTime;
}