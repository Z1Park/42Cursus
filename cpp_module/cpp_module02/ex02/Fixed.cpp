
#include <cmath>
#include "Fixed.hpp"

const int Fixed::fract_bits = 8;

Fixed::Fixed() : fp_value(0) {
}

Fixed::Fixed(const int integer) {
	fp_value = integer << fract_bits;
}

Fixed::Fixed(const float floating_num) {
	fp_value = static_cast<int>(roundf(floating_num * (1 << fract_bits)));
}


Fixed::Fixed(const Fixed &fixed){
	this->operator=(fixed);
}

Fixed::~Fixed() {
}

Fixed& Fixed::operator=(const Fixed &fixed) {
	fp_value = fixed.fp_value;
	return *this;
}

bool Fixed::operator>(const Fixed &fixed) {
	return fp_value > fixed.fp_value;
}

bool Fixed::operator<(const Fixed &fixed) {
	return fp_value < fixed.fp_value;
}

bool Fixed::operator>=(const Fixed &fixed) {
	return fp_value >= fixed.fp_value;
}

bool Fixed::operator<=(const Fixed &fixed) {
	return fp_value <= fixed.fp_value;
}

bool Fixed::operator==(const Fixed &fixed) {
	return fp_value == fixed.fp_value;
}

bool Fixed::operator!=(const Fixed &fixed) {
	return fp_value != fixed.fp_value;
}


Fixed Fixed::operator+(const Fixed &fixed) {
	Fixed tmp(*this);
	tmp.setFloat(this->toFloat() + fixed.toFloat());
	return tmp;
}

Fixed Fixed::operator-(const Fixed &fixed) {
	Fixed tmp(*this);
	tmp.setFloat(this->toFloat() - fixed.toFloat());
	return tmp;
}

Fixed Fixed::operator*(const Fixed &fixed) {
	Fixed tmp(*this);
	tmp.setFloat(this->toFloat() * fixed.toFloat());
	return tmp;
}

Fixed Fixed::operator/(const Fixed &fixed) {
	Fixed tmp(*this);
	tmp.setFloat(this->toFloat() / fixed.toFloat());
	return tmp;
}

Fixed Fixed::operator++() {
	++fp_value;
	return *this;
}

Fixed Fixed::operator++(int) {
	Fixed tmp(*this);
	++fp_value;
	return tmp;
}

Fixed Fixed::operator--() {
	--fp_value;
	return *this;
}

Fixed Fixed::operator--(int) {
	Fixed tmp(*this);
	--fp_value;
	return tmp;
}

Fixed Fixed::min(Fixed &fixedA, Fixed &fixedB) {
	return fixedA.toFloat() > fixedB.toFloat() ? fixedB : fixedA;
}

Fixed Fixed::min(const Fixed &fixedA, const Fixed &fixedB) {
	return fixedA.toFloat() > fixedB.toFloat() ? fixedB : fixedA;
}

Fixed Fixed::max(Fixed &fixedA, Fixed &fixedB) {
	return fixedA.toFloat() < fixedB.toFloat() ? fixedB : fixedA;
}

Fixed Fixed::max(const Fixed &fixedA, const Fixed &fixedB) {
	return fixedA.toFloat() < fixedB.toFloat() ? fixedB : fixedA;
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

void Fixed::setFloat(const float value) {
	fp_value = static_cast<int>(roundf(value * (1 << fract_bits)));
}


std::ostream& operator<<(std::ostream &os, const Fixed &fixed) {
	os << fixed.toFloat();
	return os;
}
