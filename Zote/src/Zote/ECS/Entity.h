#pragma once
#include <entt.hpp>
#include "Scene.h"

namespace Zote
{
	class Entity
	{
		Scene* scene;
		entt::entity id;
		TransformComponent* transform;

	public:
		Entity() {}
		Entity(entt::entity id, Scene* scene);
		Entity(const Entity& other) = default;

		TransformComponent& GetTransform() { return *transform; }

		template<typename TComponent>
		bool HasComponent()
		{
			return scene->registry.valid<TComponent>(id);
		}

		template<typename TComponent>
		TComponent& AddComponent()
		{
			return scene->registry.emplace<TComponent>(id);
		}

		template<typename TComponent>
		TComponent& GetComponent()
		{
			return scene->registry.get<TComponent>(id);
		}

		template<typename TComponent>
		void RemoveComponent()
		{
			scene->registry.erase<TComponent>(id);
		}
	};
}