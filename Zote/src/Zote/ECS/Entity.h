#pragma once
#include <entt.hpp>
#include "Scene.h"

namespace Zote
{
	class Entity
	{
		Scene* scene = nullptr;
		entt::entity id{0};
		TransformComponent* transform = nullptr;

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

		template<typename TComponent, typename... Args>
		TComponent& AddComponent(Args&&... args)
		{
			return scene->registry.emplace<TComponent>(id, std::forward<Args>(args)...);
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