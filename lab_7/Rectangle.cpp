#include "Rectangle.h"

namespace mo {
	Rectangle::Rectangle(size_t width, size_t height, Color color) :
		m_width(width), m_height(height), Shape(color) {}

	double Rectangle::square() {
		return m_width * m_height;
	}

	std::string Rectangle::toString() {
		std::stringstream string;
		string << "Rectangle" << std::endl
			<< "Color: " << colorToString(m_color) << std::endl
			<< "Width: " << m_width << std::endl
			<< "Height: " << m_height << std::endl
			<< "Square: " << square() << std::endl;
		return string.str();
	}
}