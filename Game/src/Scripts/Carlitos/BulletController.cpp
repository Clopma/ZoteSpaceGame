#include "BulletController.h"
#include "MeteoriteDestroyer.h"
#include "MeteoriteSpawner.h"


void BulletController::Update(float deltaTime)
{
	tiempoDesdeDisparo += deltaTime;
	TransformComponent& transform = GetEntity().GetComponent<TransformComponent>();
	transform.SetPosition(transform.GetPosition() + vec3(0.0f, 0.1f, 0.0f));
}

void BulletController::OnCollision(Entity entity)
{
		if (entity.GetComponent<TagComponent>().CompareName("meteorito")) {
			
				MeteoriteDestroyer* meteoriteDestroyer = new MeteoriteDestroyer();
				meteoriteDestroyer->escena = escena;
				entity.GetComponent<ScriptComponent>().AddScript(meteoriteDestroyer);
				entity.GetComponent<PBody2DComponent>().SetIsTrigger(true);
				TransformComponent& transform = GetEntity().GetComponent<TransformComponent>();
				transform.SetPosition(transform.GetPosition() + vec3(100.0f, 100.1f, 100.0f));
				if(entity.GetComponent<SpriteComponent>().color == MeteoriteSpawner::goodColor)
				{
					score.GetComponent<TransformComponent>().SetScale(
					score.GetComponent<TransformComponent>().GetScale() + vec3(0.05f, 0.f, 0.f));
				}
			
		}
}

