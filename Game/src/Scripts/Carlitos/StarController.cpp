#include "StarController.h"


void StarController::Update(float deltaTime)
{
	TransformComponent& transform = GetEntity().GetComponent<TransformComponent>();

	transform.SetPosition(transform.GetPosition() - vec3(0.0f, 0.02f, 0.0f));
	tiempoDesdeCreacion += deltaTime;
	if (tiempoDesdeCreacion > 3) {
		transform.SetPosition(vec3(transform.GetPosition().x, 2.3f, transform.GetPosition().z));
		tiempoDesdeCreacion = 0;
	}
}



