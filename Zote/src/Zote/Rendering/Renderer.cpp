#include "Renderer.h"

Zote::Renderer::Renderer(Entity* mainCamera)
	: mainCamera(mainCamera), model(1.0f), view(1.0f), projection(1.0f) {}

void Zote::Renderer::CalculateModel(TransformComponent& t)
{
	model = mat4(1.0f);
	
	model = glm::translate(model, t.GetPosition());
	model = model * glm::toMat4(t.GetRotation());
	model = glm::scale(model, t.GetScale());
}

void Zote::Renderer::CalculateProjection(float aspectRatio)
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

void Zote::Renderer::CalculateView()
{
	TransformComponent& cameraTransform = mainCamera->GetComponent<TransformComponent>();

	view = mat4(1.0f);

	view = glm::lookAt(cameraTransform.GetPosition(), cameraTransform.GetPosition()
		+ cameraTransform.GetForward(), cameraTransform.GetUp());
}
void Zote::Renderer::DrawMesh(MeshComponent& meshRenderer, TransformComponent& transform, float aspectRatio)
{
	meshRenderer.shader->Use();

	//Projection matrix
	CalculateProjection(aspectRatio);
	int projectionLocation = meshRenderer.shader->GetProjectionLocation();
	meshRenderer.shader->SetUnfiformMat4(projectionLocation, GetProjection());

	//View matrix
	CalculateView();
	int viewLocation = meshRenderer.shader->GetViewLocation();
	meshRenderer.shader->SetUnfiformMat4(viewLocation, GetView());

	//Model matrix
	CalculateModel(transform);
	int modelLocation = meshRenderer.shader->GetModelLocation();
	meshRenderer.shader->SetUnfiformMat4(modelLocation, GetModel());

	meshRenderer.texture->Use();
	meshRenderer.mesh->Render();
	meshRenderer.shader->Unbind();
}

void Zote::Renderer::DrawLight(MeshComponent& mesh, LightComponent& light)
{
	light.light->Use(mesh.shader);
}

