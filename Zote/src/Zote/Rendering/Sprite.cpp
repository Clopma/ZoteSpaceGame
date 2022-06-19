#include "Sprite.h"

namespace Zote
{
	Sprite::Sprite()
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

		m_vertexArray = MakeRef<VertexArray>();

		m_vertexBuffer = MakeRef<VertexBuffer>(vertices, sizeof(vertices[0]) * verticesCount);
	
		VertexBufferLayout layout;

		layout.Push<float>(2);
		layout.Push<float>(2);
		
		m_vertexArray->AddLayout(m_vertexBuffer, layout);

		m_indexBuffer = MakeRef<IndexBuffer>(indices, sizeof(indices[0]) * indicesCount);
		
		m_indexBuffer->Unbind();
		m_vertexBuffer->Unbind();
	}
	void Sprite::Render()
	{
		m_vertexArray->Bind();

		m_indexBuffer->Bind();
		glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);
		m_indexBuffer->Unbind();
		
		m_vertexArray->Unbind();
	}
}
