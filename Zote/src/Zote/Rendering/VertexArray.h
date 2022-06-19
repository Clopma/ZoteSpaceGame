#pragma once

#include "glew.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Utils/Memory.h"

namespace Zote
{
	class VertexArray
	{
	public:

		VertexArray();
		~VertexArray();

		void Bind() const;
		void Unbind() const;
		void AddLayout(const Ref<VertexBuffer> vb, const VertexBufferLayout& layout);
	
	private:

		uint m_rendererID = 0;
	};
}
