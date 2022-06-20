#include "Renderer.h"
#include "ECS/Entity.h"

namespace Zote
{
	Renderer::Renderer(Entity* mainCamera)
		: mainCamera(mainCamera) {}

	void Renderer::ApplyMatrixes(Ref<Shader> shader, TransformComponent& transform)
	{
		CameraComponent& camera = mainCamera->GetComponent<CameraComponent>();
		TransformComponent& cameraTransform = mainCamera->GetComponent<TransformComponent>();

		shader->Use();

		shader->SetUnfiformMat4(UNIFORM_PROJECTION, camera.GetProjection());
		shader->SetUnfiformMat4(UNIFORM_VIEW, camera.GetView(cameraTransform));
		shader->SetUnfiformMat4(UNIFORM_MODEL, transform.GetModel());

		shader->Unbind();
	}
	void Renderer::DrawMesh(Ref<Mesh> mesh, Ref<Shader> shader, Ref<Texture> texture, TransformComponent& transform)
	{
		ApplyMatrixes(shader, transform);

		shader->Use();
		texture->Use();
		mesh->Render();
		shader->Unbind();
	}

	void Renderer::DrawLine(Ref<Line> line, Ref<Shader> shader,TransformComponent& transform)
	{
		ApplyMatrixes(shader, transform);
		shader->Use();
		line->Render(shader);
	}

	void Renderer::DrawLight(MeshComponent& mesh, LightComponent& light)
	{
		light.light->Use(mesh.shader);
	}
}