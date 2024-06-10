#include "String.h"

int main() {
	mo::String str1 = "Hello";
	mo::String str2 = " World!";

	std::cout << str1 + str2 << std::endl;

	mo::String str("Hello");
	str += " World!";

	std::cout << str << std::endl;
	std::cout << str.find('l') << std::endl;
	std::cout << str.find('w') << std::endl;

	std::cin >> str;

	std::cout << str << std::endl;
	std::cout << str.find('a') << std::endl;
}