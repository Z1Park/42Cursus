
#include "File.hpp"

int	main(int ac, char **av)
{
	std::string filename;
	std::string s1;
	std::string s2;
	File file;

	if (ac != 4) {
		std::cout << "Wrong argument" << std::endl;
		return 1;
	}
	filename = av[1];
	s1 = av[2];
	s2 = av[3];
	if (s1 == "") {
		std::cout << "can't replace empty string" << std::endl;
		return 1;
	}
	if (file.printFile(filename) == false)
		return 1;
	if (file.replaceString(filename, s1, s2) == false)
		return 1;
	if (file.printFile(filename + ".replace") == false)
		return 1;
	return 0;
}
