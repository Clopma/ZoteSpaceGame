#include  "EnemyController.h"

void EnemyController::Start()
{
	thisEntity = GetEntity();
	auto& transform = thisEntity.GetComponent<TransformComponent>();
	thisEntity.AddComponent<SpriteComponent>().color = Color::Random();
	transform.SetScale(startScale);
	auto& body = thisEntity.AddComponent<PBody2DComponent>();
	body.SetMode(PBody2DComponent::Mode::dynamic);
	body.SetGScale(0);
	body.ApplyLinearImpulse(impulse);
}

void EnemyController::OnCollision(Entity entity)
{
	auto& tag = entity.GetComponent<TagComponent>();
	EnemyCollisionArgs args = 
	{
		thisEntity,
		tag.CompareTag(playerTag),
		tag.CompareTag(groundTag),
		tag.CompareTag(bulletTag)
	};
	OnCollisionEvent.Invoke(args);
}