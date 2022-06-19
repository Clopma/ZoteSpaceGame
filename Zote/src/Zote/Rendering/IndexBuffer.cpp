#include "IndexBuffer.h"

namespace Zote
{
	IndexBuffer::IndexBuffer(const uint* data, uint count)
		: m_Count(count)
	{
		glGenBuffers(1, &m_rendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint), data, GL_STATIC_DRAW);
	}
	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &m_rendererID);
	}
	void IndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
	}
	void IndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}