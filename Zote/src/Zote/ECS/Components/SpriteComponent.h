#pragma once
#include "Core.h"
#include "BaseComponent.h"

#include "Rendering/Shader.h"
#include "Rendering/Texture.h"
#include "Rendering/Mesh.h"

#include "Utils/Memory.h"
#include "Utils/CustomTypes.h"

namespace Zote
{
	struct ZOTE_API SpriteComponent : public BaseComponent
	{
		Ref<Mesh> mesh;
		Ref<Texture> texture;
		Ref<Shader> shader;

		SpriteComponent(cstr path)
		{
			//Quad data...
			float vertices[] = {
				// x	 y	   u	 v
				-0.5f, -0.5f, 0.0f, 0.0f, // 0
				 0.5f, -0.5f, 1.0f, 0.0f, // 1
				 0.5f,  0.5f, 1.0f, 1.0f, // 2
				-0.5f,	0.5f, 0.0f, 1.0f, // 3 
			};

			unsigned int indices[] = {
				0, 1, 2, //triangle 1
				2, 3, 0  //triangle 2
			};

			mesh = MakeRef<Mesh>(ZOTE_2D_MESH, true, vertices, indices, 16, 6);
			shader = MakeRef<Shader>(vertexPath, fragmentPath);
			texture = MakeRef<Texture>(path);
			texture->Load();
		}

	private:
		cstr vertexPath = "Shaders/spriteShader.vert";
		cstr fragmentPath = "Shaders/spriteShader.frag";
	};
}