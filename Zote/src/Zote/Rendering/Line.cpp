#include "Line.h"

namespace Zote
{	
	Line::Line(vec3 start, vec3 end, Color color) :
		m_color(color)
	{
		m_vertexArray = MakeRef<VertexArray>();

		float lineArray[] = {
			start.x, start.y, start.z,
			end.x, end.y, end.x
		};

		m_vertexBuffer = MakeRef<VertexBuffer>(lineArray, sizeof(lineArray[0]) * m_lineCount);

		VertexBufferLayout layout;
		layout.Push<float>(m_lineCount / 2);
		m_vertexArray->AddLayout(m_vertexBuffer, layout);

		m_vertexBuffer->Unbind();
	}

	void Line::Render(Ref<Shader> shader)
	{
		shader->Use();
		shader->SetUniformVec4(m_uniformColorName, Color::ToVec4(m_color));
		shader->Unbind();

		shader->Use();
		m_vertexArray->Bind();
		glDrawArrays(GL_LINES, 0, m_lineCount);
		m_vertexArray->Unbind();
		shader->Unbind();
	}
}