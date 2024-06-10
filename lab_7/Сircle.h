#pragma once
#include "Shape.h"

namespace mo {
	class Ñircle : public Shape {
	private:
		double m_radius;
	public:
		Ñircle(double radius, Color color);
		double square() override;
		std::string toString() override;
	};
}