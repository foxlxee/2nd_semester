#pragma once
#include "Shape.h"

namespace mo {
	class Rectangle : public Shape {
	private:
		size_t m_width;
		size_t m_height;
	public:
		Rectangle(size_t width, size_t height, Color color);
		double square() override;
		std::string toString() override;
	};
}