#include "Triangle.h"
#include "Rectangle.h"
#include "Сircle.h"

void print(mo::Shape* shapes[], size_t amount) {
	for (size_t i = 0; i < amount; i++) {
		std::cout << shapes[i]->toString() << std::endl;
	}
}

int main() {
	mo::Shape* shapes[]{
		new mo::Triangle(1, 2, mo::Color::Green),
		new mo::Rectangle(2, 5, mo::Color::Magenta),
		new mo::Rectangle(10, 20, mo::Color::Black),
		new mo::Сircle(1, mo::Color::Green),
		new mo::Triangle(1, 1, mo::Color::White),
		new mo::Сircle(5, mo::Color::Red)
	};

	print(shapes, 6);

	for (size_t i = 0; i < 6; i++) {
		delete shapes[i];
	}
}