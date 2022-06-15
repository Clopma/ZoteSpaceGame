#include "MoveTriangle.h"


void MoveTriangleScript::Start()
{
	printf("Started Triangle");
	transform = &GetEntity()->GetComponent<TransformComponent>();
}

void MoveTriangleScript::Update(float deltaTime)
{
	float dirX = 0;

	vec3 newRotation = transform->GetRotation();

	if (Input::GetKeyPressed(ZOTE_KEY_U)) //izquierda
		newRotation -= vec3(0, 1, 0) * 40.0f * deltaTime;
	else if (Input::GetKeyPressed(ZOTE_KEY_O)) //derecha
		newRotation += vec3(0, 1, 0) * 40.0f * deltaTime;

	if (Input::GetKeyPressed(ZOTE_KEY_T)) //izquierda
		newRotation -= vec3(0, 0, 1) * 40.0f * deltaTime;
	else if (Input::GetKeyPressed(ZOTE_KEY_G)) //derecha
		newRotation += vec3(0, 0, 1) * 40.0f * deltaTime;

	if(Input::GetKeyPressed(ZOTE_KEY_R)) //izquierda
		newRotation -= vec3(1, 0, 0) * 40.0f * deltaTime;
	else if (Input::GetKeyPressed(ZOTE_KEY_F)) //derecha
		newRotation += vec3(1, 0, 0) * 40.0f * deltaTime;

	transform->SetRotation(newRotation);
	//LOG(newRotation.x << ", " << newRotation.y << ", " << newRotation.z);

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

	transform->SetPosition(newPosition);
}