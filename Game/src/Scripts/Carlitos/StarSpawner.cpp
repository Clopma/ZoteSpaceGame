#include "StarSpawner.h"
#include "StarController.h"

void StarSpawner::Update(float deltaTime)
{

	transcurridoDesdeUltimaEstrella += deltaTime;

	if (estrellasCreadas < 150 && transcurridoDesdeUltimaEstrella >= 0.05f) {
		crearEstrella(vec3(RandomFloat(-3.3f, 3.3f), 2.3, 5));
		transcurridoDesdeUltimaEstrella = 0;
	}
}

void StarSpawner::crearEstrella(vec3 posicion)
{
	StarController* starController = new StarController();
	starController->escena = escena;
	//TODO meter todo esto en el controller start
	Entity meteorito = escena->CreateScriptableEntity(starController);
	TransformComponent& transform = meteorito.GetComponent<TransformComponent>();
	transform.SetPosition(posicion);
	transform.SetScale(vec3(0.07f, 0.07f, 0.0f));
	meteorito.AddComponent<SpriteComponent>("Textures/star.png");
	estrellasCreadas++;
}

