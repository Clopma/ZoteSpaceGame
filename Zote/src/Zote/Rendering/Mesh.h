#pragma once

#include <glew.h>
#include "Core.h"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include "Utils/CustomTypes.h"
#include "Utils/Memory.h"

#define ZOTE_3D_MESH 3
#define ZOTE_2D_MESH 2

namespace Zote
{
	class ZOTE_API Mesh
	{
	public:
		
		Mesh(uint mode, bool uvLayout, float* vertices, uint* indices, uint numOfVertices, uint numOfIndices);
		void Render();
	
	private:

		Ref<VertexArray> m_vertexArray;
		Ref<VertexBuffer> m_vertexBuffer;
		Ref<IndexBuffer> m_indexBuffer;
	
		const uint m_uvOffset = 2;
	};
}
