
#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal() {
	std::cout << "WrongAnimal default constructor is called" << std::endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal &animal) {
	std::cout << "WrongAnimal copy constructor is called" << std::endl;
	this->type = animal.type;
}

WrongAnimal::~WrongAnimal() {
	std::cout << "WrongAnimal destructor is called" << std::endl;
}

WrongAnimal& WrongAnimal::operator=(const WrongAnimal &animal) {
	std::cout << "WrongAnimal copy assignment operator is called" << std::endl;
	this->type = animal.type;
	return *this;
}


std::string WrongAnimal::getType() const {
	return this->type;
}

void WrongAnimal::makeSound() const {
	std::cout << "meow" << std::endl;
}
