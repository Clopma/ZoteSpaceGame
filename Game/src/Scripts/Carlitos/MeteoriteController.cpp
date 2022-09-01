#include "MeteoriteController.h"

#include "MeteoriteSpawner.h"


void MeteoriteController::Update(float deltaTime)
{

	tiempoDesdeCreacion += deltaTime;
	if (tiempoDesdeCreacion > 10) {
		((MeteoriteSpawner*) GetEntity().GetComponent<ScriptComponent>().GetScript(spawnerId))->resetearMeteorito(GetEntity()); // Creo que estoy haciendo una copia del spawner aquí...
		tiempoDesdeCreacion = 0;
	}
}


