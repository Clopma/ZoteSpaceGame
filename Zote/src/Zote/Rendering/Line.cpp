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
		Renderer::SetUniformColor(UNIFORM_LINE_COLOR, 
			shader, m_color);
		Renderer::DrawLines(m_vertexArray, shader);
	}
}