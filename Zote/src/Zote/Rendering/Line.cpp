#include "Line.h"

namespace Zote
{
	Line::Line(vec3 start, vec3 end)
	{
		vertices[0] = start.x;
		vertices[1] = start.y;
		vertices[2] = start.z;

		vertices[3] = end.x;
		vertices[4] = end.y;
		vertices[5] = end.z;

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), &vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

		//Clean
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		shader = std::make_shared<Shader>("Shaders/lineShader.vert", "Shaders/lineShader.frag");
	}

	void Line::Use()
	{
		shader->Use();

		glBindVertexArray(VAO);
		glDrawArrays(GL_LINES, 0, 6);
		glBindVertexArray(0);
	}

	Line::~Line()
	{
		if (VBO != 0)
		{
			glDeleteBuffers(1, &VBO);
			VBO = 0;
		}

		if (VAO != 0)
		{
			glDeleteVertexArrays(1, &VAO);
			VAO = 0;
		}
	}
}