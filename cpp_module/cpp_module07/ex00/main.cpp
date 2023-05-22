
#include <iostream>
#include <string>
#include "whatever.hpp"

int main() {
	{
		int a = 10;
		int b = 23;
		std::cout << "(a, b) : (" << a << ", " << b << ")" << std::endl;
		std::cout << "swap a and b" << std::endl;
		::swap(a, b);
		std::cout << "(a, b) : (" << a << ", " << b << ")" << std::endl;
		std::cout << "min : " << ::min(a, b) << std::endl;
		std::cout << "max : " << ::max(a, b) << std::endl;
	}
	{
		char a = 'Y';
		char b = 's';
		std::cout << "(a, b) : (" << a << ", " << b << ")" << std::endl;
		std::cout << "swap a and b" << std::endl;
		::swap(a, b);
		std::cout << "(a, b) : (" << a << ", " << b << ")" << std::endl;
		std::cout << "min : " << ::min(a, b) << std::endl;
		std::cout << "max : " << ::max(a, b) << std::endl;
	}
	{
		float a = 9.4;
		float b = -11.9;
		std::cout << "(a, b) : (" << a << ", " << b << ")" << std::endl;
		std::cout << "swap a and b" << std::endl;
		::swap(a, b);
		std::cout << "(a, b) : (" << a << ", " << b << ")" << std::endl;
		std::cout << "min : " << ::min(a, b) << std::endl;
		std::cout << "max : " << ::max(a, b) << std::endl;
	}
	{
		std::string a = "hello world";
		std::string b = "this is cpp";
		std::cout << "(a, b) : (" << a << ", " << b << ")" << std::endl;
		std::cout << "swap a and b" << std::endl;
		::swap(a, b);
		std::cout << "(a, b) : (" << a << ", " << b << ")" << std::endl;
		std::cout << "min : " << ::min(a, b) << std::endl;
		std::cout << "max : " << ::max(a, b) << std::endl;
	}
	return 0;
}
