#pragma once
#include <entt.hpp>
#include "Scene.h"
#include "Utils/String.h"

namespace Zote
{
	class Entity
	{
		friend class Scene;

		Scene* scene = nullptr;
		entt::entity id{0};

	public:
		str name = "Default Entity";
		str tag = "Default Tag";

		Entity() {}
		Entity(entt::entity id, Scene* scene);
		Entity(const Entity& other) = default;

		bool CompareTag(const str& otherTag) const
		{
			return tag.compare(otherTag);
		}

		template<typename TComponent>
		bool HasComponent()
		{
			return scene->registry.valid<TComponent>(id);
		}

		template<typename TComponent, typename... Args>
		TComponent& AddComponent(Args&&... args)
		{
			TComponent& component = scene->registry.emplace<TComponent>(id, std::forward<Args>(args)...);
			BaseComponent& baseComponent = static_cast<BaseComponent&>(component);
			baseComponent.entity = this;
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