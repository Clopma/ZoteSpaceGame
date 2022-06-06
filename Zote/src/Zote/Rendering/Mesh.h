#pragma once

#include <iostream>
#include <glew.h>
#include "Core.h"

namespace Zote
{
	class ZOTE_API Mesh
	{
		unsigned int VAO, VBO, IBO, indexCount;

	public:
		Mesh();
		Mesh(float* vertices, unsigned int* indices, unsigned int numOfVertices, unsigned int numOfIndices);
		~Mesh();
		void Render();
		void Clear();
	};
}
