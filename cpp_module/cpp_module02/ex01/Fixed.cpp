
#include <cmath>
#include "Fixed.hpp"

const int Fixed::fract_bits = 8;

Fixed::Fixed() : fp_value(0) {
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const int integer) {
	std::cout << "Int constructor called" << std::endl;
	fp_value = integer << fract_bits;
}

Fixed::Fixed(const float floating_num) {
	std::cout << "Float constructor called" << std::endl;
	fp_value = static_cast<int>(roundf(floating_num * (1 << fract_bits)));
}


Fixed::Fixed(const Fixed &fixed){
	std::cout << "Copy constructor called" << std::endl;
	this->operator=(fixed);
}

Fixed::~Fixed() {
	std::cout << "Destructor called" << std::endl;
}

Fixed& Fixed::operator=(const Fixed &fixed) {
	std::cout << "Copy assignment operator called" << std::endl;
	fp_value = fixed.fp_value;
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

float Fixed::toFloat() const {
	float value = (static_cast<float>(fp_value) / (1 << fract_bits));
	return value;
}

int Fixed::toInt() const {
	int value = (fp_value >> fract_bits);
	return value;
}


std::ostream& operator<<(std::ostream &os, const Fixed &fixed) {
	os << fixed.toFloat();
	return os;
}
