#include "SpriteSystem.h"
#include "ECS/Scene.h"
#include "ECS/Entity.h"

namespace Zote
{
    SpriteSystem::SpriteSystem(Scene* scene, Renderer* renderer)
        : m_scene(scene), m_renderer(renderer) {}

    void SpriteSystem::HandleSprites(float aspectRatio)
    {
		auto view = m_scene->registry.view<SpriteComponent>();

		for (auto entity : view)
		{
			SpriteComponent& sprite = view.get<SpriteComponent>(entity);
			TransformComponent& transform = sprite.GetEntity()->GetComponent<TransformComponent>();
			m_renderer->DrawSprite(sprite, transform, aspectRatio);
		}
    }
}