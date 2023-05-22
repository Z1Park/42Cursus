
#include "Cure.hpp"

Cure::Cure() {
	std::cout << "Cure default constructor is called" << std::endl;
	this->type = "cure";
}

Cure::Cure(std::string const & type) {
	std::cout << "Cure argument constructor is called" << std::endl;
	this->type = type;
}

Cure::Cure(const Cure &cure) {
	std::cout << "Cure copy constructor is called" << std::endl;
	this->type = cure.type;
}

Cure::~Cure() {
	std::cout << "Cure destructor is called" << std::endl;
}

Cure& Cure::operator=(const Cure &cure) {
	std::cout << "Cure copy assignment operator is called" << std::endl;
	this->type = cure.type;
	return *this;
}


std::string const & Cure::getType() const {
	return this->type;
}

Cure* Cure::clone() const {
	Cure *new_clone = new Cure(*this);
	return new_clone;
}

void Cure::use(ICharacter& target) {
	std::cout << "* heals " << target.getName() << "'s wounds *" << std::endl;
}
