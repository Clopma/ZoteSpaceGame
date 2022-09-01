#pragma once
#include "Core.h"
#include "BaseComponent.h"

#include <vector>

namespace Zote
{
	struct ZOTE_API Script
	{
		virtual ~Script() = default;
		friend class ScriptSystem;
		friend class ScriptComponent;

		bool enabled = true;

		Entity GetEntity() { return entity; }

		Entity CreateEntity() { return scene->CreateEntity(); }
		void DestroyEntity(Entity entity) { return scene->DestroyEntity(entity); }
		Entity& GetMainCamera() { return scene->GetMainCamera(); }

		Script() {}

		Script(const Script& other) = default;

		virtual void Start() {}
		virtual void Update(float deltaTime) {}
		virtual void OnCollision(Entity entity) {}

	private:
		Entity entity;
		Scene* scene = nullptr;
		bool started = false;
	};

	struct ZOTE_API ScriptComponent : public BaseComponent
	{
		friend class ScriptSystem;
		friend class Collision2DCheckSystem;

		ScriptComponent() {}

		ScriptComponent(const ScriptComponent& other) = default;

		int AddScript(Script* script)
		{
			script->entity = GetEntity();
			scripts.push_back(script);
			count++;
			return count - 1;
		}

		Script* GetScript(int id)
		{
			return scripts[id];
		}

		void RemoveScript(int index)
		{
			if (index < 0 || index >= count)
				return;
			delete scripts[index];
			scripts.erase(scripts.begin() + index);
		}

		void ClearScripts()
		{
			for (auto script : scripts)
				delete script;
			scripts.clear();
		}

	private:
		bool started = false;
		std::vector<Script*> scripts;
		int count = 0;
	};
}
