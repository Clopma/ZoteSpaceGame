#include "MoveTriangle.h"


void MoveTriangleScript::Start()
{
	printf("Started Triangle");
	transform = &GetEntity()->GetComponent<TransformComponent>();
}

void MoveTriangleScript::Update(float deltaTime)
{
	/*float dirX = 0;

	if (Input::GetKeyPressed(ZOTE_KEY_U))
		transform->RotateLocal(1 * deltaTime, {0, 1, 0});
	if (Input::GetKeyPressed(ZOTE_KEY_O))
		transform->RotateLocal(1 * deltaTime, {0, -1, 0});

	if (Input::GetKeyPressed(ZOTE_KEY_T))
		transform->RotateLocal(1 * deltaTime, {1, 0, 0});
	if (Input::GetKeyPressed(ZOTE_KEY_G))
		transform->RotateLocal(1 * deltaTime, {-1, 0, 0});

	vec3 newPosition = transform->GetPosition();

	if (Input::GetKeyPressed(ZOTE_KEY_I))
		newPosition += transform->GetForward() * 1.0f * deltaTime;
	if (Input::GetKeyPressed(ZOTE_KEY_K)) 
		newPosition -= transform->GetForward() * 1.0f * deltaTime;

	if (Input::GetKeyPressed(ZOTE_KEY_L))
		newPosition += transform->GetRight() * 1.0f * deltaTime;
	if (Input::GetKeyPressed(ZOTE_KEY_J))
		newPosition -= transform->GetRight() * 1.0f * deltaTime;

	if (Input::GetKeyPressed(ZOTE_KEY_Y))
		newPosition += transform->GetUp() * 1.0f * deltaTime;
	if (Input::GetKeyPressed(ZOTE_KEY_H))
		newPosition -= transform->GetUp() * 1.0f * deltaTime;

	transform->SetPosition(newPosition);*/
}

void MoveTriangleScript::OnCollision(Entity* rb)
{
	LOG("Collisioooon....");
}
