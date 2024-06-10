#pragma once
#include "Shape.h"

namespace mo {
	class �ircle : public Shape {
	private:
		double m_radius;
	public:
		�ircle(double radius, Color color);
		double square() override;
		std::string toString() override;
	};
}