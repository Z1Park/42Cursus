
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

		int getRawBits() const;
		void setRawBits(int const raw);
		float toFloat() const;
		int toInt() const;
};

std::ostream& operator<<(std::ostream &os, const Fixed &fixed);
