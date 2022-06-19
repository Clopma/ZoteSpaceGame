#include "Mesh.h"

namespace Zote
{
	Mesh::Mesh(uint mode, bool uvLayout, float* vertices, uint* indices, uint verticesCount, uint indicesCount)
    {
		m_vertexArray = MakeRef<VertexArray>();
		m_vertexBuffer = MakeRef<VertexBuffer>(vertices, sizeof(vertices[0]) * verticesCount);

		VertexBufferLayout layout;

		if (mode < ZOTE_2D_MESH || mode > ZOTE_3D_MESH)
			mode = ZOTE_3D_MESH;

		layout.Push<float>(mode);
		if (uvLayout)
			layout.Push<float>(m_uvOffset);

		m_vertexArray->AddLayout(m_vertexBuffer, layout);

		m_indexBuffer = MakeRef<IndexBuffer>(indices, sizeof(indices[0]) * indicesCount);

		m_indexBuffer->Unbind();
		m_vertexBuffer->Unbind();
    }
	void Mesh::Render()
	{
		m_vertexArray->Bind();
		m_indexBuffer->Bind();
		glDrawElements(GL_TRIANGLES, m_indexBuffer->GetCount(), GL_UNSIGNED_INT, 0);
		m_indexBuffer->Unbind();
		m_vertexArray->Unbind();
	}
}