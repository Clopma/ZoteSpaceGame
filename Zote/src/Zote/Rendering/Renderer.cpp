#include "Renderer.h"

Zote::Renderer::Renderer(std::shared_ptr<CameraComponent> mainCam_Camera, std::shared_ptr<TransformComponent> mainCam_Transform)
	: mainCam_Camera(mainCam_Camera), mainCam_Transform(mainCam_Transform), model(1.0f), view(1.0f), projection(1.0f) {}

void Zote::Renderer::CalculateModel(TransformComponent& t)
{
	model = mat4(1.0f);
	if (t.rotation.x != 0)
		model = glm::rotate(model, glm::radians(t.rotation.x), glm::vec3(1, 0, 0));
	if (t.rotation.y != 0)
		model = glm::rotate(model, glm::radians(t.rotation.y), glm::vec3(0, 1, 0));
	if (t.rotation.z != 0)
		model = glm::rotate(model, glm::radians(t.rotation.z), glm::vec3(0, 0, 1));

	//Translation and scale
	model = glm::translate(model, t.position);
	model = glm::scale(model, t.scale);
}

void Zote::Renderer::UpdateCameraAxis()
{
	mainCam_Camera->front.x = glm::cos(glm::radians(mainCam_Camera->yaw)) * glm::cos(glm::radians(mainCam_Camera->pitch));
	mainCam_Camera->front.y = glm::sin(glm::radians(mainCam_Camera->pitch));
	mainCam_Camera->front.z = glm::sin(glm::radians(mainCam_Camera->yaw)) * glm::cos(glm::radians(mainCam_Camera->pitch));
	mainCam_Camera->front = glm::normalize(mainCam_Camera->front);

	mainCam_Camera->right = glm::normalize(glm::cross(mainCam_Camera->front, mainCam_Camera->worldUp));
	mainCam_Camera->up = glm::normalize(glm::cross(mainCam_Camera->right, mainCam_Camera->front));
}

void Zote::Renderer::CalculateProjection(float aspectRatio)
{
	projection = mat4(1.0f);
	projection = glm::perspective(mainCam_Camera->fov, aspectRatio, mainCam_Camera->near, mainCam_Camera->far);
}

void Zote::Renderer::CalculateView()
{
	view = mat4(1.0f);
	view = glm::lookAt(mainCam_Transform->position, mainCam_Transform->position + mainCam_Camera->front, mainCam_Camera->up);
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

	meshRenderer.mesh->Render();
	meshRenderer.shader->Unbind();
}
