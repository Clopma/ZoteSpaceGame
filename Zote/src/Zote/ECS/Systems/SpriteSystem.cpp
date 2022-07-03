#include "MeshSystem.h"

#include "ECS/Entity.h"
#include "ECS/Scene.h"
#include "ECS/Components/SpriteComponent.h"
#include "ECS/Components/TransformComponent.h"
#include "ECS/Components/CameraComponent.h"

#include "Rendering/Renderer.h"
#include "Rendering/Mesh.h"
#include "Utils/GlobalStrings.h"

namespace Zote
{
    SpriteSystem::SpriteSystem(Scene* scene)
        : m_scene(scene) {}

    void SpriteSystem::HandleSprites()
    {
		auto& camera = m_scene->GetMainCamera().GetComponent<CameraComponent>();
		auto& cameraTransform = m_scene->GetMainCamera().GetComponent<TransformComponent>();

		auto view = m_scene->registry.view<SpriteComponent>();

		for (auto entity : view)
		{
			auto& spriteComponent = view.get<SpriteComponent>(entity);
			auto& transformComponent = spriteComponent.GetEntity()->GetComponent<TransformComponent>();

			if (spriteComponent.HasTexture())
				spriteComponent.texture->Use();

			Renderer::SetUniformColor(UNIFORM_SPRITE_COLOR, spriteComponent.shader, spriteComponent.color);
			Renderer::SetUniformFloat(UNIFORM_SPRITE_HAS_TEXTURE, spriteComponent.shader, 
				spriteComponent.HasTexture() ? 1.0f : 0.0f);

			spriteComponent.mesh->Render(spriteComponent.shader,
				camera.GetProjection(), camera.GetView(cameraTransform), transformComponent.GetModel());
		}
    }
}