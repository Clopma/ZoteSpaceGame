#include "MeteoriteSpawner.h"
#include "MeteoriteController.h"

void MeteoriteSpawner::Update(float deltaTime)
{
	transcurridoDesdeUltimaDificultad += deltaTime;
	float test2 = test;
	
	if(iniciando && transcurridoDesdeUltimaDificultad > 0.3f || transcurridoDesdeUltimaDificultad > 10)
	{
		LOG(iniciando);
		MeteoriteController* meteoriteController = new MeteoriteController();
		meteoriteController->escena = escena;
		//TODO meter en el controller start?
		Entity meteorito = escena->CreateScriptableEntity(meteoriteController);
		meteoritos.push_back(resetearMeteorito(meteorito));
		transcurridoDesdeUltimaDificultad = 0;
	}
}

Entity MeteoriteSpawner::resetearMeteorito(Entity meteorito)
{
	TransformComponent& transform = meteorito.GetComponent<TransformComponent>();
	transform.SetScale(VEC3_ONE * RandomFloat(0.2f, 0.45f));
	meteorito.GetComponent<TagComponent>().name = "meteorito";
	if (meteorito.HasComponent<SpriteComponent>())
	{
		iniciando = false;
		SpriteComponent& sprite_component = meteorito.GetComponent<SpriteComponent>();
		sprite_component.AddTexture("Textures/meteoritoFrame1.png");
	} else
	{
		meteorito.AddComponent<SpriteComponent>("Textures/meteoritoFrame1.png").color = (RandomFloat(0, 1) > 0.8) ? goodColor : badColor;
	}
	
	if (meteorito.HasComponent<PBody2DComponent>())
	{
		meteorito.RemoveComponent<PBody2DComponent>();
	}
	transform.SetPosition(vec3(RandomFloat(-3.3f, 3.3f), 2.3, 1.0f));
	meteorito.AddComponent<PBody2DComponent>();
	auto& body = meteorito.GetComponent<PBody2DComponent>();
	body.SetMode(PBody2DComponent::Mode::dynamic);
	body.SetGScale(0);
	body.SetColliderSize({0.8f, 0.8f});
	body.ApplyLinearImpulse(vec2(RandomFloat(-0.025f, 0.015f), RandomFloat(-0.10f, -0.15f)));
	
	
	return meteorito;
}

