#pragma once

#include "Utils/CustomTypes.h"
#include <glew.h>

namespace Zote
{
	class IndexBuffer
	{
	public:
		IndexBuffer(const uint* data, uint size);
		~IndexBuffer();

		void Bind() const;
		void Unbind() const;

		uint GetCount() const { return m_Count; }

	private:
		uint m_rendererID = 0;
		uint m_Count = 0;
	};
}
