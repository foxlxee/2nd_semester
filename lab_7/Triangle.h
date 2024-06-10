#pragma once
#include "Shape.h"

namespace mo {
	class Triangle : public Shape {
	private:
		double m_base;
		double m_height;
	public:
		Triangle(double base, double height, Color color);
		double square() override;
		std::string toString() override;
	};
}