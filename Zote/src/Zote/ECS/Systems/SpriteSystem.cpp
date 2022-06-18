#include "SpriteSystem.h"
#include "ECS/Scene.h"

namespace Zote
{
    SpriteSystem::SpriteSystem(Scene* scene, Renderer* renderer)
        : m_scene(scene), m_renderer(renderer) {}

    void SpriteSystem::HandleSprites(float aspectRatio)
    {
		/*auto group = m_scene->registry.group<TransformComponent>(entt::get<SpriteComponent>);
		for (auto entity : group)
		{
			SpriteComponent& sprite = group.get<SpriteComponent>(entity);
			TransformComponent& transform = group.get<TransformComponent>(entity);
			m_renderer->DrawSprite(sprite, transform, aspectRatio);
		}*/
    }
}