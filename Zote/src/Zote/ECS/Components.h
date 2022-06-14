#pragma once
#include "Core.h"
#include "Rendering/Mesh.h"
#include "Rendering/Shader.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "Rendering/Window.h"
#include <glm/gtc/type_ptr.hpp>
#include <memory>

#include "Rendering/Texture.h"

namespace Zote
{
	class Entity;

	struct ZOTE_API BaseComponent
	{
		friend class Entity;

		bool enabled = true;

		Entity* GetEntity() { return entity; }

	private:
		Entity* entity;
	};

	struct ZOTE_API TransformComponent : public BaseComponent
	{
		friend class Scene;

		using vec3 = glm::vec3;

		vec3 position = { 0, 0, 0 };
		vec3 rotation = { 0, 0, 0 };
		vec3 scale = { 1, 1, 1 };

		TransformComponent() {}

		TransformComponent(const TransformComponent& other) = default;

		vec3 GetForward() 
		{ 
			forward.x = glm::cos(glm::radians(rotation.y)) * glm::cos(glm::radians(rotation.x));
			forward.y = glm::sin(glm::radians(rotation.x));
			forward.z = glm::sin(glm::radians(rotation.y)) * glm::cos(glm::radians(rotation.x));

			forward = glm::normalize(forward);
			return forward; 
		}
		vec3 GetRight()  
		{
			right = glm::normalize(glm::cross(GetForward(), { 0, 1, 0 }));
			return right; 
		}
		vec3 GetUp()  
		{
			up = glm::normalize(glm::cross(GetRight(), GetForward()));
			return up;
		}

	private:
		vec3 right = { 0, 0, 0 };
		vec3 up = { 0, 0, 0 };
		vec3 forward = { 0, 0, 0 };
	};

	struct ZOTE_API MeshComponent : public BaseComponent
	{
		std::shared_ptr<Mesh> mesh;
		std::shared_ptr<Shader> shader;
		std::shared_ptr<Texture> texture;

		MeshComponent()
		{
			float vertices[] = {
				//x     y      z     u     v
				-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
				 0.0f, -1.0f, 1.0f, 0.5f, 0.0f,
				 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
				 0.0f,  1.0f, 0.0f, 0.5f, 1.0f
			};
			unsigned int indices[] = {
					0, 3, 1,
					1, 3, 2,
					2, 3, 0,
					0, 1, 2
			};
			mesh = std::make_shared<Mesh>(vertices, indices, 20, 12);
			shader = std::make_shared<Shader>();
			texture = std::make_shared<Texture>("Textures/brick.png");
			texture->Load();
		}

		MeshComponent(const MeshComponent& other) = default;
	};

	struct ZOTE_API CameraComponent : public BaseComponent
	{
		float fov, near, far;

		CameraComponent() :
			fov(45.f), near(0.1f), far(100.0f) {}

		CameraComponent(const CameraComponent& other) = default;
	};

	struct ZOTE_API Script
	{
		friend class Scene;
		friend class ScriptComponent;

		bool enabled = true;

		Entity* GetEntity() { return entity; }

		Script() {}

		Script(const Script& other) = default;

		virtual void Start() {}
		virtual void Update(float deltaTime) {}

	private:
		Entity* entity = nullptr;
		bool started = false;
	};

	struct ZOTE_API ScriptComponent : public BaseComponent
	{
		friend class Scene;

		ScriptComponent() {}

		ScriptComponent(const ScriptComponent& other) = default;

		int AddScript(Script* script)
		{
			script->entity = GetEntity();
			scripts.push_back(script);
			count++;
			return count - 1;
		}

		void RemoveScript(int index)
		{
			if (index < 0 || index >= count)
				return;
			delete scripts[index];
			scripts.erase(scripts.begin() + index);
		}

		~ScriptComponent()
		{
			for (auto script : scripts)
				delete script;
			scripts.clear();
		}

	private:
		bool started = false;
		std::vector<Script*> scripts;
		int count = 0;
	};
}
