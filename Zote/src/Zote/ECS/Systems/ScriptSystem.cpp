#include "ScriptSystem.h"
#include "ECS/Scene.h"

namespace Zote
{
	ScriptSystem::ScriptSystem(Scene* scene)
		: m_scene(scene) {}

	void ScriptSystem::HandleScripts(float deltaTime)
	{
		auto view = m_scene->registry.view<ScriptComponent>();

		for (auto entity : view)
		{
			ScriptComponent& scriptComponent = view.get<ScriptComponent>(entity);

			if (!scriptComponent.enabled)
				return;

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
}