#pragma once
#include "Core.h"
#include "BaseComponent.h"

#include "Rendering/Mesh.h"
#include "Rendering/Shader.h"
#include "Rendering/Texture.h"

#include "Utils/Memory.h"

namespace Zote
{
	struct ZOTE_API MeshComponent : public BaseComponent
	{
		Ref<Mesh> mesh;
		Ref<Shader> shader;
		Ref<Texture> texture;

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
			mesh = MakeRef<Mesh>(vertices, indices, 20, 12);
			shader = MakeRef<Shader>();
			texture = MakeRef<Texture>("Textures/brick.png");
			texture->Load();
		}

		MeshComponent(const MeshComponent& other) = default;
	};
}