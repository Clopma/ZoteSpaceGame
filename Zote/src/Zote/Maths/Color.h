#pragma once

namespace Zote
{
	struct Color
	{
		float r, g, b, a;

		Color();
		Color(float r, float g, float b, float a);

		static const Color grey;
	};
}


