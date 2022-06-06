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
	struct ZOTE_API Transform
	{
		using vec3 = glm::vec3;

		vec3 position;
		vec3 rotation;
		vec3 scale;

		Transform()
			: position(0, 0, 0), rotation(0, 0, 0), scale(1, 1, 1), model(1.0f) 
		{
			LOG("Transform component created!");
		}
		Transform(const Transform& other) = default;

		~Transform() { LOG("Transform component destroyed!") }

		void CalculateModel()
		{
			model = glm::mat4(1.0f);

			//Rotation
			if (rotation.x != 0)
				model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1, 0, 0));
			if (rotation.y != 0)
				model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
			if (rotation.z != 0)
				model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1));

			//Translation and scale
			model = glm::translate(model, position);
			model = glm::scale(model, scale);
		}

		float* GetModel() { return glm::value_ptr(model); }

	private:
		glm::mat4 model;
	};

	struct ZOTE_API MeshRenderer
	{
		std::shared_ptr<Mesh> mesh;
		std::shared_ptr<Shader> shader;

		MeshRenderer()
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

		MeshRenderer(const MeshRenderer& other) = default;
	};

	struct ZOTE_API Camera
	{
		float fov, near, far;
		glm::vec3 worldUp;

		Camera()
			: fov(45.f), near(0.1f), far(100.0f), yaw(-90), 
			  pitch(0), worldUp(0, 1, 0)
		{
			projection = new glm::mat4(1.0f);
			view = new glm::mat4(1.0f);
;			right = new glm::vec3();
			front = new glm::vec3();
			up = new glm::vec3();
		}

		Camera(const Camera& camera) = default;

		void CalculateProjection(float windowAspect) { *projection = glm::perspective(fov, windowAspect, near, far); }

		void CalculateView(const Transform& transform) { *view = glm::lookAt(transform.position, transform.position + *front, *up); }

		float* GetProjection() { return glm::value_ptr(*projection); }
		float* GetView() { return glm::value_ptr(*view); }

		void UpdateAxis()
		{
			front->x = glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
			front->y = glm::sin(glm::radians(pitch));
			front->z = glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
			*front = glm::normalize(*front);

			*right = glm::normalize(glm::cross(*front, worldUp));
			*up = glm::normalize(glm::cross(*right, *front));
		}

		~Camera() 
		{
			delete right;
			delete up;
			delete front;

			delete projection;
			delete view;
		}

	private:
		glm::vec3* right;
		glm::vec3* up;
		glm::vec3* front;
		float yaw, pitch;

		glm::mat4* projection;
		glm::mat4* view;
	};
}
