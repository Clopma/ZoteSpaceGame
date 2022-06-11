#include "MoveTriangle.h"


void MoveTriangleScript::Start()
{
	printf("Started Triangle");
	transform = &GetEntity()->GetComponent<TransformComponent>();
	//transform = &GetEntity()->GetTransform();
}

void MoveTriangleScript::Update(float deltaTime)
{
	float dir = 0;

	bool aPressed = Input::GetKeyPressed(ZOTE_KEY_A);
	bool dPressed = Input::GetKeyPressed(ZOTE_KEY_D);

	if (aPressed)
		dir = -1;
	else if (dPressed)
		dir = 1;

	//transform->position.x += dir * speed * deltaTime;
}