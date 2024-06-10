#include "Ñircle.h"

namespace mo {
	Ñircle::Ñircle(double radius, Color color) :
		m_radius(radius), Shape(color) {}

	double Ñircle::square() {
		return acos(-1) * m_radius * m_radius;
	}

	std::string Ñircle::toString() {
		std::stringstream string;
		string << "Circle" << std::endl
			<< "Color: " << colorToString(m_color) << std::endl
			<< "Radius: " << m_radius << std::endl
			<< "Square: " << square() << std::endl;
		return string.str();
	}
}