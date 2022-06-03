#include "Color.h"

namespace Zote 
{
	Color::Color()
		: r(0), g(0), b(0), a(0) {}

	Color::Color(float r, float g, float b, float a)
		: r(r), g(g), b(b), a(a) {}

	const Color Color::grey(0.009f, 0.008f, 0.007f, 1.0f);
}