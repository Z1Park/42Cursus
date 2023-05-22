
#include "Scalar.hpp"

Scalar::Scalar() : value("") {
}

Scalar::Scalar(const Scalar& ref) : value(ref.value) {
}

Scalar::~Scalar() {
}

Scalar&	Scalar::operator=(const Scalar& ref) {
	this->value = ref.value;
	return *this;
}


std::string Scalar::getValue() const {
	return this->value;
}

void Scalar::setValue(std::string value) {
	this->value  = value;
}

std::ostream& operator<<(std::ostream& os, Scalar &scalar) {
	std::string value = scalar.getValue();

	if (value == "nan" || value == "nanf") {
		os << "char: impossible" << std::endl;
		os << "int: impossible" << std::endl;
		os << "float: " << std::sqrt(-1) << "f" << std::endl;
		os << "double: " << std::sqrt(-1);
	}
	else if (value == "inf" || value == "+inf" || value == "inff" || value == "+inff") {
		os << "char: impossible" << std::endl;
		os << "int: impossible" << std::endl;
		float f = __FLT_MAX__ * 1000;
		os << "float: " << f << "f" << std::endl;
		double d = __DBL_MAX__ * 1000;
		os << "double: " << d;
	}
	else if (value == "-inf" || value == "-inff") {
		os << "char: impossible" << std::endl;
		os << "int: impossible" << std::endl;
		float f = __FLT_MAX__ * -1000;
		os << "float: " << f << "f" << std::endl;
		double d = __DBL_MAX__ * -1000;
		os << "double: " << d;
	}
	else {
		int temp = (value.length() == 1 && std::isdigit(value[0]) == 0) ? \
				value[0] : std::atoi(value.c_str());
		if (std::isprint(temp) != 0)
			os << "char: '" << static_cast<char>(temp) << "'" << std::endl;
		else
			os << "char: Non displayable" << std::endl;
		if (value.length() == 1 && std::isdigit(value[0]) == 0) {
			os << "int: " << static_cast<int>(value[0]) << std::endl;
			os << "float: " << static_cast<float>(value[0]) << ".0f" << std::endl;
			os << "double: " << static_cast<double>(value[0]) << ".0" << std::endl;
		}
		else {
			os << "int: " << std::atoi(value.c_str()) << std::endl;
			int point_flag = false;
			if (std::atof(value.c_str()) == static_cast<float>(std::atoi(value.c_str())))
				point_flag = true;
			os << "float: " << static_cast<float>(std::atof(value.c_str()))
				<< ((point_flag) ? ".0f" : "f") << std::endl;
			os << "double: " << std::atof(value.c_str())
				<< ((point_flag) ? ".0" : "");
		}
	}
	return os;
}
