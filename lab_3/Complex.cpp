#include "Complex.h"

namespace mo {
	Complex::Complex() : Complex(0,0) {}

	Complex::Complex(double realPart, double imaginaryPart)
		: m_realPart(realPart), m_imaginaryPart(imaginaryPart) {}

	Complex::Complex(const Complex& number) :
		Complex(number.m_realPart, number.m_imaginaryPart) {}

	Complex::~Complex() {}

	Complex Complex::add(const Complex& number) {
		return Complex(m_realPart + number.m_realPart, m_imaginaryPart + number.m_imaginaryPart);
	}

	Complex Complex::subtract(const Complex& number) {
		return Complex(m_realPart - number.m_realPart, m_imaginaryPart - number.m_imaginaryPart);
	}

	Complex Complex::multiply(const Complex& number) {
		return Complex(
			(m_realPart * number.m_realPart) - (m_imaginaryPart * number.m_imaginaryPart),
			(m_realPart * number.m_imaginaryPart) + (number.m_realPart * m_imaginaryPart));
	}

	Complex Complex::operator +(const Complex& number) {
		return add(number);
	}

	Complex Complex::operator -(const Complex& number) {
		return subtract(number);
	}

	Complex Complex::operator *(const Complex& number) {
		return multiply(number);
	}
	
	void Complex::operator ++() {
		m_realPart++;
	}

	void Complex::operator --() {
		m_realPart--;
	}

	void Complex::operator =(const Complex& number) {
		m_realPart = number.m_realPart;
		m_imaginaryPart = number.m_imaginaryPart;
	}

	void Complex::operator +=(const Complex& number) {
		*this = add(number);
	}

	void Complex::operator -=(const Complex& number) {
		*this = subtract(number);
	}

	void Complex::operator *=(const Complex& number) {
		*this = multiply(number);
	}

	std::ostream& operator <<(std::ostream& os, const Complex& number) {
		os << number.m_realPart;
		if (number.m_imaginaryPart >= 0) {
			os << '+';
		}
		os << number.m_imaginaryPart << 'i';
		return os;
	}

	std::istream& operator >>(std::istream& is, Complex& number) {
		is >> number.m_realPart;
		is >> number.m_imaginaryPart;
		return is;
	}
}