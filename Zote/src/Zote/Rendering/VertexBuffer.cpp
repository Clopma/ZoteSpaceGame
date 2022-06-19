#include "VertexBuffer.h"

namespace Zote
{
	VertexBuffer::VertexBuffer(const void* data, uint size)
	{
		glGenBuffers(1, &m_rendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}
	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_rendererID);
	}
	void VertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
	}
	void VertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}