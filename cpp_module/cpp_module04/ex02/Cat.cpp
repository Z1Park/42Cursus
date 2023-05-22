
#include "Cat.hpp"

Cat::Cat() {
	std::cout << "Cat default constructor is called" << std::endl;
	this->type = "Cat";
	this->brain = new Brain();
}

Cat::Cat(const Cat &cat) {
	std::cout << "Cat copy constructor is called" << std::endl;
	this->type = cat.type;
	this->brain = new Brain(*(cat.brain));
}

Cat::~Cat() {
	std::cout << "Cat destructor is called" << std::endl;
	delete this->brain;
}

Cat& Cat::operator=(const Cat &cat) {
	std::cout << "Cat copy assignment operator is called" << std::endl;
	this->type = cat.type;
	delete this->brain;
	this->brain = new Brain(*(cat.brain));
	return *this;
}


std::string Cat::getType() const {
	return this->type;
}

void Cat::makeSound() const {
	std::cout << "moew" << std::endl;
}

Brain *Cat::getBrain() const {
	return this->brain;
}
