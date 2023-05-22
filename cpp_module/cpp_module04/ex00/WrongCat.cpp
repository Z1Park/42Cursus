
#include "WrongCat.hpp"

WrongCat::WrongCat() {
	std::cout << "WrongCat default constructor is called" << std::endl;
	this->type = "WrongCat";
}

WrongCat::WrongCat(const WrongCat &cat) {
	std::cout << "WrongCat copy constructor is called" << std::endl;
	this->type = cat.type;
}

WrongCat::~WrongCat() {
	std::cout << "WrongCat destructor is called" << std::endl;
}

WrongCat& WrongCat::operator=(const WrongCat &cat) {
	std::cout << "WrongCat copy assignment operator is called" << std::endl;
	this->type = cat.type;
	return *this;
}


std::string WrongCat::getType() const {
	return this->type;
}

void WrongCat::makeSound() const {
	std::cout << "bark! bark!" << std::endl;
}
