#include "Entity.h"

namespace Zote
{
	Entity::Entity(entt::entity id, Scene* scene)
		: id(id), scene(scene)
	{
		AddComponent<TransformComponent>();
	}
}