
#pragma once
#include <iostream>
#include <string>

class Fixed {
	private:
		int fp_value;
		static const int fract_bits;

	public:
		Fixed();
		Fixed(Fixed &fixed);
		~Fixed();
		Fixed& operator=(Fixed &fixed);

		int getRawBits() const;
		void setRawBits(int const raw);
};
