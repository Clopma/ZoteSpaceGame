#pragma once

#include "Core.h"
#include "ECS/Components/ScriptComponent.h"

namespace Zote
{
	class Scene;

	class ZOTE_API ScriptSystem
	{
		Scene* m_scene = nullptr;

	public:
		ScriptSystem(Scene* scene);
		void HandleScripts(float deltaTime);
	};
}