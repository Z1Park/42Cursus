
#include "Scalar.hpp"

int main(int ac, char **av) {
	Scalar scalar;

	if (ac != 2) {
		std::cerr << "wrong argument" << std::endl;
		return 1;
	}
	scalar.setValue(av[1]);
	std::cout << scalar << std::endl;
	return 0;
}
