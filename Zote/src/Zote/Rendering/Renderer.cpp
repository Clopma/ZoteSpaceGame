#include "Renderer.h"

Zote::Renderer::Renderer(Entity* mainCamera)
	: mainCamera(mainCamera), model(1.0f), view(1.0f), projection(1.0f) {}

void Zote::Renderer::CalculateModel(TransformComponent& t)
{
	model = mat4(1.0f);
	
	model = glm::scale(model, t.scale);

	model = glm::rotate(model, glm::radians(t.rotation.x), glm::vec3(1, 0, 0));
	model = glm::rotate(model, glm::radians(t.rotation.y), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(t.rotation.z), glm::vec3(0, 0, 1));

	model = glm::translate(model, t.position);
}

void Zote::Renderer::UpdateCameraAxis()
{
	CameraComponent& camera = mainCamera->GetComponent<CameraComponent>();
	vec3 cameraRot = mainCamera->GetComponent<TransformComponent>().rotation;

	camera.front.x = glm::cos(glm::radians(cameraRot.y)) * glm::cos(glm::radians(cameraRot.x));
	camera.front.y = glm::sin(glm::radians(cameraRot.x));
	camera.front.z = glm::sin(glm::radians(cameraRot.y)) * glm::cos(glm::radians(cameraRot.x));

	camera.front = glm::normalize(camera.front);
	camera.right = glm::normalize(glm::cross(camera.front, camera.worldUp));
	camera.up = glm::normalize(glm::cross(camera.right, camera.front));
}

void Zote::Renderer::CalculateProjection(float aspectRatio)
{
	CameraComponent& camera = mainCamera->GetComponent<CameraComponent>();

	projection = mat4(1.0f);
	projection = glm::perspective(camera.fov, aspectRatio, camera.near, camera.far);
}

void Zote::Renderer::CalculateView()
{
	CameraComponent& camera = mainCamera->GetComponent<CameraComponent>();
	TransformComponent& cameraTransform = mainCamera->GetComponent<TransformComponent>();

	view = mat4(1.0f);

	view = glm::lookAt(cameraTransform.position, cameraTransform.position + camera.front, camera.up);
}

void Zote::Renderer::DrawMesh(MeshComponent& meshRenderer, TransformComponent& transform, float aspectRatio)
{
	meshRenderer.shader->Use();

	UpdateCameraAxis();

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
