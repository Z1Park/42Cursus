
#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <limits>

class Scalar {
	private:
		std::string value;

	public:
		Scalar();
		Scalar(const Scalar& ref);
		~Scalar();
		Scalar&	operator=(const Scalar& ref);

		std::string getValue() const;
		void setValue(std::string value);
};

std::ostream& operator<<(std::ostream& os, Scalar &scalar);
