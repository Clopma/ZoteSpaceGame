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

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		vb = MakeRef<VertexBuffer>(vertices, sizeof(vertices[0]) * verticesCount);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 4, 0);

		ib = MakeRef<IndexBuffer>(indices, sizeof(indices[0]) * indicesCount);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FLOAT, sizeof(vertices[0]) * 4, (void*)(sizeof(vertices[0]) * 2));	
		
		ib->Unbind();
		vb->Unbind();
		glBindVertexArray(0);
	}
	void Sprite::Render()
	{
		glBindVertexArray(VAO);
		
		ib->Bind();
		glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);
		ib->Unbind();
		
		glBindVertexArray(0);
	}
	Sprite::~Sprite()
	{
		if (VAO != 0)
		{
			glDeleteVertexArrays(1, &VAO);
			VAO = 0;
		}
	}
}
