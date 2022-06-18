#include "LightSystem.h"
#include "ECS/Scene.h"

namespace Zote
{
	LightSystem::LightSystem(Scene* scene, Renderer* renderer)
		: m_scene(scene), m_renderer(renderer) {}

	void LightSystem::HandleLights()
	{
		auto lightView = m_scene->registry.view<LightComponent>();
		auto meshView = m_scene->registry.view<MeshComponent>();

		for (auto lightEntity : lightView)
		{
			auto& light = lightView.get<LightComponent>(lightEntity);

			for (auto meshEntity : meshView)
			{
				auto& mesh = meshView.get<MeshComponent>(meshEntity);
				m_renderer->DrawLight(mesh, light);
			}
		}
	}
}