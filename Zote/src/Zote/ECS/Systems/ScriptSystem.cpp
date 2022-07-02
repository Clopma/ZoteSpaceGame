#include "ScriptSystem.h"
#include "ECS/Scene.h"

#include "box2d/b2_api.h"
#include "box2d/b2_math.h"
#include "box2d/b2_shape.h"
#include "box2d/b2_fixture.h"

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

		//Agrupamos todos los ScriptsComponents que tengan un PBody2DComponent
		//auto group = m_scene->registry.group<ScriptComponent>(entt::get<PBody2DComponent>);

		auto rb_script_view = m_scene->registry.view<ScriptComponent, PBody2DComponent>();

		for (auto script_entity : rb_script_view) //Para cada uno...
		{
			auto& scriptComponent = rb_script_view.get<ScriptComponent>(script_entity);

			if (scriptComponent.count == 0) continue; //Si no tiene scripts se pasa al siguiente

			auto& currentRb = rb_script_view.get<PBody2DComponent>(script_entity); //Obtenemos su PBody2DComponent
			auto view_allRb = m_scene->registry.view<PBody2DComponent>(); //Agrupamos todos los PBody2DComponent

			for (auto rb_entity : view_allRb)
			{
				auto& otherRb = view_allRb.get<PBody2DComponent>(rb_entity);
				
				if (currentRb.GetEntity() == otherRb.GetEntity()) continue; //Omitimos el suyo propio

				bool collision = b2TestOverlap(currentRb.m_fixture->GetShape(), 0, otherRb.m_fixture->GetShape(), 0,
					currentRb.m_body->GetTransform(), otherRb.m_body->GetTransform()); //Comprobamos si colisiona con alguno de los demás

				if (!collision) continue;

				for (auto script : scriptComponent.scripts)
					script->OnCollision(otherRb.GetEntity()); //Si colisiona ejecutamos el OnCollision de todos sus scripts
			}
		}
	}
}