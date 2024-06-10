#include "Shape.h"

namespace mo {
	std::string colorToString(Color color) {
		switch (color) {
		case Color::White:
			return "White";
		case Color::Black:
			return "Black";
		case Color::Red:
			return "Red";
		case Color::Green:
			return "Green";
		case Color::Blue:
			return "Blue";
		case Color::Magenta:
			return "Magenta";
		}

		return std::string();
	}

	Shape::Shape(Color color) {
		m_color = color;
	}

	void Shape::setColor(Color color) {
		m_color = color;
	}

	Color Shape::color() {
		return m_color;
	}
}