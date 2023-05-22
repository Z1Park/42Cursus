
#include "Dog.hpp"

Dog::Dog() {
	std::cout << "Dog default constructor is called" << std::endl;
	this->type = "Dog";
	this->brain = new Brain();
}

Dog::Dog(const Dog &dog) {
	std::cout << "Dog copy constructor is called" << std::endl;
	this->type = dog.type;
	this->brain = new Brain(*(dog.brain));
}

Dog::~Dog() {
	std::cout << "Dog destructor is called" << std::endl;
	delete this->brain;
}

Dog& Dog::operator=(const Dog &dog) {
	std::cout << "Dog copy assign operator is called" << std::endl;
	this->type = dog.type;
	delete this->brain;
	this->brain = new Brain(*(dog.brain));
	return *this;
}


std::string Dog::getType() const {
	return this->type;
}

void Dog::makeSound() const {
	std::cout << "bark! bark!" << std::endl;
}

Brain *Dog::getBrain() const {
	return this->brain;
}
