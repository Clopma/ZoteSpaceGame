#include "Renderer.h"

namespace Zote
{
	void Renderer::SetUniformMatrix(const cstr uniformName, Ref<Shader> shader, const mat4& matrix)
	{
		shader->Use();
		shader->SetUnfiformMat4(uniformName, matrix);
		shader->Unbind();
	}

	void Renderer::DrawTriangles(const Ref<VertexArray> vertexArray, const Ref<IndexBuffer> indexBuffer, const Ref<Shader> shader)
	{
		shader->Use();
		vertexArray->Bind();
		indexBuffer->Bind();
		glDrawElements(GL_TRIANGLES, indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
		indexBuffer->Unbind();
		vertexArray->Unbind();
		shader->Unbind();
	}
	void Renderer::DrawLines(const Ref<VertexArray> vertexArray, const Ref<Shader> shader)
	{
		shader->Use();
		vertexArray->Bind();
		glDrawArrays(GL_LINES, 0, 6); //two 3D vectors (6 floats)
		vertexArray->Unbind();
		shader->Unbind();
	}
}