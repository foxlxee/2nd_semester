#pragma once
#include <iostream>
#include <sstream>

namespace mo {
	enum class Color {
		White,
		Black,
		Red,
		Green,
		Blue,
		Magenta
	};

	std::string colorToString(Color color);

	class Shape {
	protected:
		Color m_color;
	public:
		Shape(Color color);
		void setColor(Color color);
		Color color();
		virtual double square() = 0;
		virtual std::string toString() = 0;
	};
}
