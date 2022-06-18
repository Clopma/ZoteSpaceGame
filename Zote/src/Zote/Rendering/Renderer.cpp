#include "Renderer.h"
#include "ECS/Entity.h"

namespace Zote
{
	Renderer::Renderer(Entity* mainCamera)
		: mainCamera(mainCamera), model(1.0f), view(1.0f), projection(1.0f) {}

	void Renderer::CalculateModel(TransformComponent& t)
	{
		model = mat4(1.0f);

		model = glm::translate(model, t.GetPosition());
		model = model * glm::toMat4(t.GetRotation());
		model = glm::scale(model, t.GetScale());
	}

	void Renderer::CalculateProjection(float aspectRatio)
	{
		CameraComponent& camera = mainCamera->GetComponent<CameraComponent>();

		if (camera.mode == CameraComponent::Mode::Ortographic)
		{
			vec2 size = camera.size;
			projection = glm::ortho(-size.x, size.x, -size.y, size.y, camera.near, camera.far);
			return;
		}

		if (camera.mode == CameraComponent::Mode::Perspective)
		{
			projection = glm::perspective(camera.fov, aspectRatio, camera.near, camera.far);
			return;
		}
	}

	void Renderer::CalculateView()
	{
		TransformComponent& cameraTransform = mainCamera->GetComponent<TransformComponent>();

		view = mat4(1.0f);

		view = glm::lookAt(cameraTransform.GetPosition(), cameraTransform.GetPosition()
			+ cameraTransform.GetForward(), cameraTransform.GetUp());
	}
	void Renderer::DrawMesh(MeshComponent& meshRenderer, TransformComponent& transform, float aspectRatio)
	{
		meshRenderer.shader->Use();

		//Projection matrix
		CalculateProjection(aspectRatio);
		meshRenderer.shader->SetUnfiformMat4(projectionUniformName, projection);

		//View matrix
		CalculateView();
		meshRenderer.shader->SetUnfiformMat4(viewUniformName, view);

		//Model matrix
		CalculateModel(transform);
		meshRenderer.shader->SetUnfiformMat4(modelUniformName, model);

		meshRenderer.texture->Use();
		meshRenderer.mesh->Render();
		meshRenderer.shader->Unbind();
	}

	void Renderer::DrawSprite(SpriteComponent& sprite, TransformComponent& transform, float aspectRatio)
	{
		sprite.shader->Use();

		//Projection matrix
		CalculateProjection(aspectRatio);
		sprite.shader->SetUnfiformMat4(projectionUniformName, projection);

		//View matrix
		CalculateView();
		sprite.shader->SetUnfiformMat4(viewUniformName, view);

		//Model matrix
		CalculateModel(transform);
		sprite.shader->SetUnfiformMat4(modelUniformName, model);

		sprite.sprite->Render();
		sprite.shader->Unbind();
	}

	void Renderer::DrawLight(MeshComponent& mesh, LightComponent& light)
	{
		light.light->Use(mesh.shader);
	}
}