#include "Complex.h"

int main() {
	setlocale(LC_ALL, "Russian");

	mo::Complex firstNumber;
	std::cin >> firstNumber;
	std::cout << "Первое число: " << firstNumber << std::endl;

	mo::Complex secondNumber;
	std::cin >> secondNumber;
	std::cout << "Второе число: " << secondNumber << std::endl;

	std::cout << "Сумма: " << (firstNumber + secondNumber) << std::endl;
	std::cout << "Разность: " << (firstNumber - secondNumber) << std::endl;
	std::cout << "Произведение: " << (firstNumber * secondNumber) << std::endl;
}