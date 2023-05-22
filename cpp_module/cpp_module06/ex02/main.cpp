
#include <stdlib.h>
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

Base *generate() {
	srand(std::time(NULL));
	int random_value = rand();
	Base *base;

	if (random_value % 3 == 0)
		base = new A();
	else if (random_value % 3 == 1)
		base = new B();
	else
		base = new C();
	return base;
}

void identify(Base *p) {
	if (dynamic_cast<A*>(p)) {
		std::cout << "The type of Base is A" << std::endl;
		return;
	}
	if (dynamic_cast<B*>(p)) {
		std::cout << "The type of Base is B" << std::endl;
		return;
	}
	if (dynamic_cast<C*>(p)) {
		std::cout << "The type of Base is C" << std::endl;
		return;
	}
}

void identify(Base &p) {
	try {
		__attribute__((unused)) A &a = dynamic_cast<A&>(p);
		std::cout << "The type of Base is A" << std::endl;
		return;
	} catch (std::exception&) {}
	try {
		__attribute__((unused)) B &b = dynamic_cast<B&>(p);
		std::cout << "The type of Base is B" << std::endl;
	} catch (std::exception&) {}
	try {
		__attribute__((unused)) C &c = dynamic_cast<C&>(p);
		std::cout << "The type of Base is C" << std::endl;
	} catch (std::exception&) {}
}

int main() {
	Base *base = generate();

	identify(base);
	identify(*base);

	return 0;
}
