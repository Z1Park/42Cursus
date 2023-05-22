
#include "Animal.hpp"

Animal::Animal() {
	std::cout << "Animal default constructor is called" << std::endl;
}

Animal::Animal(const Animal &animal) {
	std::cout << "Animal copy constructor is called" << std::endl;
	this->type = animal.type;
}

Animal::~Animal() {
	std::cout << "Animal destructor is called" << std::endl;
}

Animal& Animal::operator=(const Animal &animal) {
	std::cout << "Animal copy assignment operator is called" << std::endl;
	this->type = animal.type;
	return *this;
}


std::string Animal::getType() const {
	return this->type;
}
