#pragma once
#include <iostream>

namespace mo {
	class Complex {
	private:
		double m_realPart;
		double m_imaginaryPart;
	public:
		Complex();
		Complex(double realPart, double imaginaryPart);
		Complex(const Complex& number);
		~Complex();

		Complex add(const Complex& number);
		Complex subtract(const Complex& number);
		Complex multiply(const Complex& number);
		
		Complex operator +(const Complex& number);
		Complex operator -(const Complex& number);
		Complex operator *(const Complex& number);
		void operator =(const Complex& number);
		void operator +=(const Complex& number);
		void operator -=(const Complex& number);
		void operator *=(const Complex& number);
		void operator ++();
		void operator --();

		friend std::ostream& operator <<(std::ostream& os, const Complex& number);
		friend std::istream& operator >>(std::istream& is, Complex& number);
	};
}