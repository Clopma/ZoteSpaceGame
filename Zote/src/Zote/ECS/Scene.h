#pragma once
#include <entt.hpp>
#include "Core.h"
#include "Rendering/Mesh.h"
#include "Rendering/Shader.h"
#include "Rendering/Window.h"
#include "glm/glm.hpp"
#include "Event.h"

namespace Zote
{
	struct ZOTE_API Transform
	{
		using vec3 = glm::vec3;

		vec3 position;
		vec3 rotation;
		vec3 scale;

		Transform()
			: position(vec3(0, 0, 0)), rotation(vec3(0, 0, 0)), scale(vec3(1, 1, 1)) {}
		Transform(const Transform& other) = default;
	};

	struct ZOTE_API MeshRenderer
	{
		Mesh mesh;
		Shader shader;

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
			mesh = Mesh(vertices, indices, 12, 12);
		}
		MeshRenderer(const MeshRenderer& other) = default;
	};

	class ZOTE_API Scene
	{

	public:
		Scene() {}
		Scene(Window& window);
		void RenderEntities(OnRenderArgs args);

		Scene(const Scene& other) {};
	
	private:
		entt::registry registry;
	};
}

