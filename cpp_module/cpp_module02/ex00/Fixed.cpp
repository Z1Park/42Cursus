
#include "Fixed.hpp"

const int Fixed::fract_bits = 8;

Fixed::Fixed() : fp_value(0) {
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(Fixed &fixed){
	std::cout << "Copy constructor called" << std::endl;
	this->operator=(fixed);
}

Fixed::~Fixed() {
	std::cout << "Destructor called" << std::endl;
}

Fixed& Fixed::operator=(Fixed &fixed) {
	std::cout << "Copy assignment operator called" << std::endl;
	fp_value = fixed.getRawBits();
	return *this;
}


int Fixed::getRawBits() const {
	std::cout << "getRawBits member function called" << std::endl;
	return this->fp_value;
}

void Fixed::setRawBits(int const raw) {
	std::cout << "setRawBits member function called" << std::endl;
	this->fp_value = raw;
}
