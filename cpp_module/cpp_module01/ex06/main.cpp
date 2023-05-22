
#include "Harl.hpp"

int	main(int ac, char **av)
{
	Harl harl;

	if (ac == 1) {
		std::cout << "======test lowercase======" << std::endl;
		harl.complain("debug");
		harl.complain("info");
		harl.complain("warning");
		harl.complain("error");
		std::cout << std::endl;

		std::cout << "======test uppercase======" << std::endl;
		harl.complain("DEBUG");
		harl.complain("INFO");
		harl.complain("WARNING");
		harl.complain("ERROR");
	}
	else if (ac == 2)
		harl.filteredComplain(av[1]);
	else
		std::cout << "you enter too many arguments" << std::endl;
	return 0;
}
