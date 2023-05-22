
#pragma once
#include <iostream>
#include <string>

class Fixed {
	private:
		int fp_value;
		static const int fract_bits;

	public:
		Fixed();
		Fixed(const int integer);
		Fixed(const float floating_num);
		Fixed(const Fixed &fixed);
		~Fixed();
		Fixed& operator=(const Fixed &fixed);

		bool operator>(const Fixed &fixed);
		bool operator<(const Fixed &fixed);
		bool operator>=(const Fixed &fixed);
		bool operator<=(const Fixed &fixed);
		bool operator==(const Fixed &fixed);
		bool operator!=(const Fixed &fixed);

		Fixed operator+(const Fixed &fixed);
		Fixed operator-(const Fixed &fixed);
		Fixed operator*(const Fixed &fixed);
		Fixed operator/(const Fixed &fixed);

		Fixed operator++();
		Fixed operator++(int);
		Fixed operator--();
		Fixed operator--(int);

		static Fixed min(Fixed &fixedA, Fixed &fixedB);
		static Fixed min(const Fixed &fixedA, const Fixed &fixedB);
		static Fixed max(Fixed &fixedA, Fixed &fixedB);
		static Fixed max(const Fixed &fixedA, const Fixed &fixedB);

		int getRawBits() const;
		void setRawBits(int const raw);
		float toFloat() const;
		int toInt() const;
		void setFloat(const float value);
};

std::ostream& operator<<(std::ostream &os, const Fixed &fixed);
