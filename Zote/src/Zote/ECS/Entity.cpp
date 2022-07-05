#include "Entity.h"
#include "Components/TransformComponent.h"
#include "Components/TagComponent.h"

namespace Zote
{
	Entity::Entity(entt::entity id, Scene* scene, str name, str tag)
		: scene(scene), id(id)
	{
		AddComponent<TransformComponent>();
		auto& tagComp = AddComponent<TagComponent>();
		tagComp.name = name;
		tagComp.tag = tag;
	}
}