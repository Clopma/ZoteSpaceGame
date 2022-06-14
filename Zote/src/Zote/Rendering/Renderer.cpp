#include "Renderer.h"

Zote::Renderer::Renderer(Entity* mainCamera)
	: mainCamera(mainCamera), model(1.0f), view(1.0f), projection(1.0f) {}

void Zote::Renderer::CalculateModel(TransformComponent& t)
{
	model = mat4(1.0f);
	
	model = glm::translate(model, t.position);

	model = glm::rotate(model, glm::radians(t.rotation.x), glm::vec3(1, 0, 0));
	model = glm::rotate(model, glm::radians(t.rotation.y), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(t.rotation.z), glm::vec3(0, 0, 1));

	model = glm::scale(model, t.scale);
}

void Zote::Renderer::CalculateProjection(float aspectRatio)
{
	CameraComponent& camera = mainCamera->GetComponent<CameraComponent>();

	projection = mat4(1.0f);
	projection = glm::perspective(camera.fov, aspectRatio, camera.near, camera.far);
}

void Zote::Renderer::CalculateView()
{
	TransformComponent& cameraTransform = mainCamera->GetComponent<TransformComponent>();

	view = mat4(1.0f);

	view = glm::lookAt(cameraTransform.position, cameraTransform.position 
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
