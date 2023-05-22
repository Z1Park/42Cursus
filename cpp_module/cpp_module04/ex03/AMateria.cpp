
#include "AMateria.hpp"

AMateria::AMateria() {
	std::cout << "AMateria default constructor is called" << std::endl;
}

AMateria::AMateria(std::string const & type) {
	std::cout << "AMateria argument constructor is called" << std::endl;
	this->type = type;
}

AMateria::AMateria(const AMateria &amateria) {
	std::cout << "AMateria copy constructor is called" << std::endl;
	this->type = amateria.type;
}

AMateria::~AMateria() {
	std::cout << "AMateria destructor is called" << std::endl;
}

AMateria& AMateria::operator=(const AMateria &amateria) {
	std::cout << "AMateria copy assignment operator is called" << std::endl;
	this->type = amateria.type;
	return *this;
}


std::string const & AMateria::getType() const {
	return this->type;
}

void AMateria::use(ICharacter& target) {
	std::cout << "use Materia to " << target.getName()
		<< ", but nothing happens" << std::endl;
}
