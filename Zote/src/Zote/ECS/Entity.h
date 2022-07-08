#pragma once
#include <entt.hpp>
#include "Scene.h"
#include "Utils/String.h"

namespace Zote
{
	class Entity
	{
		Scene* scene = nullptr;
		entt::entity id{0};

	public:
		Entity() {}
		Entity(entt::entity id, Scene* scene, str name = "Entity", str tag = "Default");
		Entity(const Entity& other) = default;

		entt::entity GetId() const { return id; }

		bool operator==(Entity other)
		{
			return id == other.id;
		}

		template<typename TComponent>
		bool HasComponent()
		{
			return scene->registry.try_get<TComponent>(id);
		}

		template<typename TComponent, typename... Args>
		TComponent& AddComponent(Args&&... args)
		{
			TComponent& component = scene->registry.emplace<TComponent>(id, std::forward<Args>(args)...);
			BaseComponent& baseComponent = static_cast<BaseComponent&>(component);
			baseComponent.entity = *this;
			scene->OnComponentAdded(id);
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