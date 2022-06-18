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
#include "Rendering/Line.h"
#include <glm/gtx/quaternion.hpp>
#include "Rendering/Lighting/Light.h"
#include "Maths/Color.h"
#include "Rendering/Sprite.h"

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
		using vec3 = glm::vec3;

		TransformComponent() {}

		TransformComponent(const TransformComponent& other) = default;

		void SetPosition(const vec3& newPos) { position = newPos; }
		const vec3& GetPosition() const { return position; }
		
		void SetScale(const vec3& newScale) { scale = newScale; }
		const vec3& GetScale() const { return scale; }
		
		void SetRotation(const glm::quat& newRot) { rotation = newRot; UpdateAxis(); }
		const glm::quat& GetRotation() const { return rotation; }

		const vec3& GetForward() const { return forward; }
		const vec3& GetRight() const { return right; }
		const vec3& GetUp() const { return up; }

		void RotateLocal(const float& degrees, const glm::vec3& axis)
		{
			rotation = rotation * glm::normalize(glm::angleAxis(degrees, axis));
			rotation = glm::normalize(rotation);
			UpdateAxis();
		}

		void RotateGlobal(const float& degrees, const glm::vec3& axis)
		{
			rotation = glm::normalize(glm::angleAxis(degrees, axis)) * rotation;
			rotation = glm::normalize(rotation);
			UpdateAxis();
		}
		
	private:

		vec3 position = { 0, 0, 0 };
		glm::quat rotation = { 1, 0, 0, 0 };
		vec3 scale = { 1, 1, 1 };

		vec3 right = { 1, 0, 0 };
		vec3 up = { 0, 1, 0 };
		vec3 forward = { 0, 0, 1 };	

		void UpdateAxis()
		{
			mat4 axis = glm::mat4(1.0f);

			axis = axis * glm::toMat4(rotation);		

			forward = axis * vec4(0, 0, 1, 0);
			right = -axis * vec4(1, 0, 0, 0);
			up = axis * vec4(0, 1, 0, 0);
		}
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

	struct ZOTE_API SpriteComponent
	{
		template<typename T>
		using Ref = std::shared_ptr<T>;

		Ref<Sprite> sprite;
		Ref<Shader> shader;

		SpriteComponent()
		{
			sprite = std::make_shared<Sprite>();
			shader = std::make_shared<Shader> (sprite->GetVertPath(), sprite->GetFragPath());
		}
	};

	struct ZOTE_API CameraComponent : public BaseComponent
	{
		enum class Mode { Perspective, Ortographic };

		Mode mode = Mode::Ortographic;

		float fov = 45.f;
		float near = 0.1f;
		float far = 100.0f;

		glm::vec2 size = { 2.f, 2.f };

		CameraComponent() {}

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

	struct ZOTE_API LightComponent : public BaseComponent
	{
		friend class Renderer;

		const Color& GetColor() const { return light->m_color; }
		void SetColor(const Color& newColor) { light->m_color = newColor; }

		const float& GetIntensity() const { return light->m_intensity; }
		void SetIntensity(const float& newIntens) { light->m_intensity = newIntens; }

		LightComponent() 
		{
			light = std::make_shared<Light>();
		}
		LightComponent(const LightComponent& other) = default;

	private:
		std::shared_ptr<Light> light;
	};
}
