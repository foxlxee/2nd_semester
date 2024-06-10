#pragma once
#include <iostream>

namespace mo {
	class String {
	private:
		char* m_str;
		size_t m_length;

		String(char* str, size_t length);
		void _delete();
	public:
		String();
		String(const char* str);
		String(const String& string);
		~String();

		String concat(const String& string);
		bool equals(const String& string);
		size_t length();
		int find(char c);
		char& at(size_t index);
		char* c_str();

		void operator=(const String& string);
		void operator=(const char* string);
		char& operator[](size_t index);
		String operator+(const String& string);
		String operator+(const char* string);
		void operator+=(const String& string);
		void operator+=(const char* string);
		bool operator <(const String& string);
		bool operator >(const String& string);
		bool operator ==(const String& string);

		friend std::ostream& operator <<(std::ostream& os, const String& string);
		friend std::istream& operator >>(std::istream& is, String& string);
	};
}