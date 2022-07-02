#pragma once

#include "Core.h"
#include "Utils/Math.h"

namespace Zote
{
	struct ZOTE_API Color
	{
		float r, g, b, a;

		Color();
		Color(float r, float g, float b, float a);

		static const Color grey;
		static const Color red;
		static const Color green;
		static const Color blue;
		
		static Color Normalize(const Color& color);
	};
}