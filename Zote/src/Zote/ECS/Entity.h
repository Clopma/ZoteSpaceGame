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

		template<typename TComponent>
		TComponent& AddComponent()
		{
			TComponent& component = scene->registry.emplace<TComponent>(id);
			BaseComponent& baseComponent = static_cast<BaseComponent&>(component);
			baseComponent.entity = this;
			return component;
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