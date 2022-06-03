#include "Color.h"

namespace Zote 
{
	Color::Color()
		: r(0), g(0), b(0), a(0) {}

	Color::Color(float r, float g, float b, float a)
		: r(r), g(g), b(b), a(a) {}

	Color Color::Normalize(const Color& color)
	{
		Color c;
		c.r = color.r / 255;
		c.g = color.g / 255;
		c.b = color.b / 255;
		c.a = 1;
		return c;
	}

	const Color Color::grey(108.0f, 122.0f, 137.0f, 1.0f);
}