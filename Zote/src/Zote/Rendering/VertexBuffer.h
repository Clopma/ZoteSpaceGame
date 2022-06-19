#pragma once

#include "Utils/CustomTypes.h"
#include <glew.h>

namespace Zote
{
	class VertexBuffer
	{
	public:
		VertexBuffer(const void* data, uint size);
		~VertexBuffer();

		void Bind() const;
		void Unbind() const;

	private:
		uint m_rendererID = 0;
	};
}
