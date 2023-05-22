
#include "Cat.hpp"

Cat::Cat() {
	std::cout << "Cat default constructor is called" << std::endl;
	this->type = "Cat";
}

Cat::Cat(const Cat &cat) {
	std::cout << "Cat copy constructor is called" << std::endl;
	this->type = cat.type;
}

Cat::~Cat() {
	std::cout << "Cat destructor is called" << std::endl;
}

Cat& Cat::operator=(const Cat &cat) {
	std::cout << "Cat copy assignment operator is called" << std::endl;
	this->type = cat.type;
	return *this;
}


std::string Cat::getType() const {
	return this->type;
}

void Cat::makeSound() const {
	std::cout << "moew" << std::endl;
}
