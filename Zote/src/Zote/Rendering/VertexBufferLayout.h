#pragma once

#include <vector>
#include "Utils/CustomTypes.h"
#include <glew.h>

struct VertexBufferElement
{
	uint type;
	uint count;
	uchar normalized;

	static uint GetTypeSize(uint type)
	{
		switch (type)
		{
			case GL_FLOAT: return 4;
			case GL_UNSIGNED_INT: return 4;
			case GL_UNSIGNED_BYTE: return 1;
		}
		return 0;
	}
};

class VertexBufferLayout
{
private:

	std::vector<VertexBufferElement> m_elements;
	uint m_stride = 0;

public:

	VertexBufferLayout() {}

	template<typename T>
	void Push(uint count) {}

	template<>
	void Push<float>(uint count)
	{
		m_elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_stride += VertexBufferElement::GetTypeSize(GL_FLOAT) * count;
	}

	template<>
	void Push<uint>(uint count)
	{
		m_elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_stride += VertexBufferElement::GetTypeSize(GL_UNSIGNED_INT) * count;
	}

	template<>
	void Push<uchar>(uint count)
	{
		m_elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_stride += VertexBufferElement::GetTypeSize(GL_UNSIGNED_BYTE) * count;
	}

	const std::vector<VertexBufferElement>& GetElements() const { return m_elements; }
	uint GetStride() const { return m_stride; }
};