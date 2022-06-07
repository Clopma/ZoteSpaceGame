#pragma once
#include "ECS/Components.h"
#include <memory>
#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>

namespace Zote
{
	class ZOTE_API Renderer
	{
		using mat4 = glm::mat4;
		using vec3 = glm::vec3;

		CameraComponent* mainCam_Camera;
		TransformComponent* mainCam_Transform;

		mat4 model;
		mat4 view;
		mat4 projection;		

		void CalculateModel(TransformComponent& t);

		void UpdateCameraAxis();

		void CalculateProjection(float aspectRatio);

		void CalculateView();

		float* GetProjection() { return glm::value_ptr(projection); }
		float* GetView() { return glm::value_ptr(view); }
		float* GetModel() { return glm::value_ptr(model); }

	public:

		Renderer() {}

		Renderer(TransformComponent& cam_transform, CameraComponent& cam_Camera);

		void DrawMesh(MeshComponent& meshRenderer, TransformComponent& transform, float aspectRatio);

		~Renderer();
	};
}
