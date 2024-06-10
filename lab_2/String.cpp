#include "String.h"

#define BUFFER_SIZE 128

char* _concat(const char* firstStr, size_t firstStrLength, const char* secondStr, size_t secondStrLength) {
	size_t newLength = firstStrLength + secondStrLength;
	char* result = new char[newLength + 1];
	result[newLength] = 0;

	std::copy(firstStr, firstStr + firstStrLength, result);
	std::copy(secondStr, secondStr + secondStrLength, result + firstStrLength);

	return result;
}

namespace mo {
	String::String() : m_length(0), m_str(nullptr) { }

	String::String(char* str, size_t length) : m_str(str), m_length(length) { }

	String::String(const char* str) : m_length(strlen(str)) {
		m_str = new char[m_length + 1];
		m_str[m_length] = 0;

		std::copy(str, str + m_length, m_str);
	}

	String::String(const String& string) {
		if (string.m_length > 0) {
			m_str = new char[string.m_length + 1];
			m_str[string.m_length] = 0;
			m_length = string.m_length;

			std::copy(string.m_str, string.m_str + string.m_length, m_str);
			return;
		}

		m_length = 0;
		m_str = nullptr;
	}

	String::~String() {
		_delete();
	}

	void String::_delete() {
		if (m_length > 0) {
			delete m_str;
		}
	}

	String String::concat(const String& string) {
		return String(
			_concat(m_str, m_length, string.m_str, string.m_length),
			m_length + string.m_length);
	}

	bool String::equals(const String& string) {
		if (m_length != string.m_length) {
			return false;
		}

		for (size_t i = 0; i < m_length; i++) {
			if (m_str[i] != string.m_str[i]) {
				return false;
			}
		}

		return true;
	}

	size_t String::length() {
		return m_length;
	}
	
	int String::find(char c) {
		for (size_t i = 0; i < m_length; i++) {
			if (m_str[i] == c) {
				return i;
			}
		}

		return -1;
	}
	
	char& String::at(size_t index) {
		if (index >= m_length) {
			throw new std::exception("index is out of range");
		}

		return m_str[index];
	}
	
	char* String::c_str() {
		return m_str;
	};

	void String::operator=(const String& string) {
		_delete();
		
		m_str = new char[string.m_length + 1];
		m_length = string.m_length;

		std::copy(string.m_str, string.m_str + string.m_length + 1, m_str);
	}

	void String::operator=(const char* string) {
		_delete();

		size_t length = strlen(string);

		m_str = new char[length + 1];
		m_length = length;

		std::copy(string, string + length + 1, m_str);
	}

	char& String::operator[](size_t index) {
		return at(index);
	}
	
	String String::operator+(const String& string) {
		return concat(string);
	}

	String String::operator+(const char* string) {
		size_t length = strlen(string);

		return String(_concat(m_str, m_length, string, strlen(string)), m_length + length);
	}

	void String::operator+=(const String& string) {
		char* newStr = _concat(
			m_str,
			m_length,
			string.m_str,
			string.m_length);

		_delete();

		m_str = newStr;
		m_length = m_length + string.m_length;
	}

	void String::operator+=(const char* string) {
		size_t length = strlen(string);

		char* newStr = _concat(
			m_str,
			m_length,
			string,
			length);

		_delete();
		
		m_str = newStr;
		m_length = m_length + length;
	}

	bool String::operator <(const String& string) {
		return m_length < string.m_length;
	}
	
	bool String::operator >(const String& string) {
		return m_length > string.m_length;
	}

	bool String::operator ==(const String& string) {
		return equals(string);
	}

	std::ostream& operator <<(std::ostream& os, const String& string) {
		os << string.m_str;
		return os;
	}

	std::istream& operator >>(std::istream& is, String& string) {
		char buffer[BUFFER_SIZE];
		is.getline(buffer, BUFFER_SIZE);

		for (size_t i = 0; i < BUFFER_SIZE; i++) {
			if (buffer[i] == 0) {
				string._delete();

				string.m_length = i;
				string.m_str = new char[i + 1];
				string.m_str[i] = 0;

				std::copy(buffer, buffer + i, string.m_str);

				break;
			}
		}

		return is;
	}
}