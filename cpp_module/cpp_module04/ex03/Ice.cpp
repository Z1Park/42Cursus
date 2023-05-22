
#include "Ice.hpp"

Ice::Ice() {
	std::cout << "Ice default constructor is called" << std::endl;
	this->type = "ice";
}

Ice::Ice(std::string const & type) {
	std::cout << "Ice argument constructor is called" << std::endl;
	this->type = type;
}

Ice::Ice(const Ice &ice) {
	std::cout << "Ice copy constructor is called" << std::endl;
	this->type = ice.type;
}

Ice::~Ice() {
	std::cout << "Ice destructor is called" << std::endl;
}

Ice& Ice::operator=(const Ice &ice) {
	std::cout << "Ice copy assignment operator is called" << std::endl;
	this->type = ice.type;
	return *this;
}


std::string const & Ice::getType() const {
	return this->type;
}

Ice* Ice::clone() const {
	Ice *new_clone = new Ice(*this);
	return new_clone;
}

void Ice::use(ICharacter& target) {
	std::cout << "* shoots an ice bolt at " << target.getName() << " *" << std::endl;
}
