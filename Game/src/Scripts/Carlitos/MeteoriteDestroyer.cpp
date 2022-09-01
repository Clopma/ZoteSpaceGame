#include "MeteoriteDestroyer.h"

#include "MeteoriteSpawner.h"


void MeteoriteDestroyer::Update(float deltaTime)
{
	if (destruido)
	{
		return;
	}
	SpriteComponent& sprite = GetEntity().GetComponent<SpriteComponent>();
	GetEntity().GetComponent<PBody2DComponent>().SetIsTrigger(false);
	tiempoDesdeImpakto += deltaTime;
	
	if (tiempoDesdeImpakto < 0.15f){
		sprite.AddTexture("Textures/meteoritoFrame2.png");
		
	} else if (tiempoDesdeImpakto < 0.3f) {

		sprite.AddTexture("Textures/meteoritoFrame3.png");
		
	} else if (tiempoDesdeImpakto < 0.45f) {
		
		sprite.AddTexture("Textures/meteoritoFrame4.png");
		
	} else if (tiempoDesdeImpakto < 0.6f) {
		
		sprite.AddTexture("Textures/meteoritoFrame5.png");
		
	} else 
	{
		((MeteoriteSpawner*) GetEntity().GetComponent<ScriptComponent>().GetScript(spawnerId))->resetearMeteorito(GetEntity());
		destruido = true;
	}
}


