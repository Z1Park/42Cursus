
#include "Bureaucrat.hpp"

int main() {
	try {
		Bureaucrat bureaucrat("bureaucrat A", 79);
		std::cout << bureaucrat << std::endl;
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	try {
		Bureaucrat bureaucrat("bureaucrat B", -1);
		std::cout << bureaucrat << std::endl;
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	try {
		Bureaucrat bureaucrat("bureaucrat C", 158);
		std::cout << bureaucrat << std::endl;
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}

	try {
		Bureaucrat bureaucrat("bureaucrat D", 2);
		std::cout << bureaucrat << std::endl;
		bureaucrat.increseGrade();
		std::cout << bureaucrat << std::endl;
		bureaucrat.increseGrade();
		std::cout << bureaucrat << std::endl;
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	try {
		Bureaucrat bureaucrat("bureaucrat E", 149);
		std::cout << bureaucrat << std::endl;
		bureaucrat.decreseGrade();
		std::cout << bureaucrat << std::endl;
		bureaucrat.decreseGrade();
		std::cout << bureaucrat << std::endl;
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
