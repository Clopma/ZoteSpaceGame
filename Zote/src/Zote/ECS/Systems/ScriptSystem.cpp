#include "ScriptSystem.h"

#include "ECS/Scene.h"
#include "ECS/Components/ScriptComponent.h"

namespace Zote
{
	ScriptSystem::ScriptSystem(Scene* scene)
		: m_scene(scene) 
	{
		m_scene->OnDestroyEntity.AddListener(new Delegate<OnDestroyEntityArgs>(this, &ScriptSystem::OnDestroyEntity));
	}

	void ScriptSystem::HandleScripts(float deltaTime)
	{
		auto view = m_scene->registry.view<ScriptComponent>();

		for (auto entity : view)
		{
			ScriptComponent& scriptComponent = view.get<ScriptComponent>(entity);

			if (!scriptComponent.enabled || scriptComponent.count == 0)
				continue;

			for (auto script : scriptComponent.scripts)
			{
				if ((!script->enabled))
					continue;

				if (!script->started)
				{
					script->Start();
					script->started = true;
				}

				script->Update(deltaTime);
			}
		}		
	}
	void ScriptSystem::OnDestroyEntity(OnDestroyEntityArgs args)
	{
		if (args.entity->HasComponent<ScriptComponent>())
			args.entity->GetComponent<ScriptComponent>().ClearScripts();
	}
}