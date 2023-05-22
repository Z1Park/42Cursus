
#include "Dog.hpp"

Dog::Dog() {
	std::cout << "Dog default constructor is called" << std::endl;
	this->type = "Dog";
}

Dog::Dog(const Dog &dog) {
	std::cout << "Dog copy constructor is called" << std::endl;
	this->type = dog.type;
}

Dog::~Dog() {
	std::cout << "Dog destructor is called" << std::endl;
}

Dog& Dog::operator=(const Dog &dog) {
	std::cout << "Dog copy assign operator is called" << std::endl;
	this->type = dog.type;
	return *this;
}


std::string Dog::getType() const {
	return this->type;
}

void Dog::makeSound() const {
	std::cout << "bark! bark!" << std::endl;
}
