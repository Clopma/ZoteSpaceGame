#pragma once
#include "Core.h"
#include "Rendering/Mesh.h"
#include "Rendering/Shader.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "Rendering/Window.h"
#include <glm/gtc/type_ptr.hpp>
#include <memory>

namespace Zote
{
	struct ZOTE_API TransformComponent
	{
		using vec3 = glm::vec3;

		vec3 position;
		vec3 rotation;
		vec3 scale;

		TransformComponent()
			: position(0, 0, 0), rotation(0, 0, 0), scale(1, 1, 1) 
		{
			LOG("Transform component created!");
		}
		TransformComponent(const TransformComponent& other) = default;

		~TransformComponent() { LOG("Transform component destroyed!") }
	};

	struct ZOTE_API MeshComponent
	{
		std::shared_ptr<Mesh> mesh;
		std::shared_ptr<Shader> shader;

		MeshComponent()
		{
			float vertices[] = {
				-1.0f, -1.0f, 0.0f,
				 0.0f, -1.0f, 1.0f,
				 1.0f, -1.0f, 0.0f,
				 0.0f,  1.0f, 0.0f
			};
			unsigned int indices[] = {
					0, 3, 1,
					1, 3, 2,
					2, 3, 0,
					0, 1, 2
			};
			mesh = std::make_shared<Mesh>(vertices, indices, 12, 12);
			shader = std::make_shared<Shader>();
		}

		MeshComponent(const MeshComponent& other) = default;
	};

	struct ZOTE_API CameraComponent
	{
		using vec3 = glm::vec3;
		float fov, near, far, yaw, pitch;

		vec3 right;
		vec3 up;
		vec3 front;
		vec3 worldUp;

		CameraComponent() :
			fov(45.f), near(0.1f), far(100.0f), yaw(-90), pitch(0),
			right(0, 0, 0), up(0, 0, 0), front(0, 0, 0), worldUp(0, 1, 0) {}

		CameraComponent(const CameraComponent& camera) = default;
	};
}
