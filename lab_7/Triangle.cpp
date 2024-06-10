#include "Triangle.h"

namespace mo {
	Triangle::Triangle(double base, double height, Color color) :
		m_base(base), m_height(height), Shape(color) {}

	double Triangle::square() {
		return (m_height * m_base) / 2;
	}

	std::string Triangle::toString() {
		std::stringstream string;
		string << "Triangle" << std::endl
			<< "Color: " << colorToString(m_color) << std::endl
			<< "Height: " << m_height << std::endl
			<< "Base: " << m_base << std::endl
			<< "Square: " << square() << std::endl;
		return string.str();
	}
}