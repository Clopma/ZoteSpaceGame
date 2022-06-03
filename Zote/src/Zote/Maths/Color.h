#pragma once
#include "../Core.h"

namespace Zote
{
	struct ZOTE_API Color
	{
		float r, g, b, a;

		Color();
		Color(float r, float g, float b, float a);

		static const Color grey;

		static Color Normalize(const Color& color);
	};
}


