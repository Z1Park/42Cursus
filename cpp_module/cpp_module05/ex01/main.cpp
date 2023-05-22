
#include "Bureaucrat.hpp"
#include "Form.hpp"

int main() {
	try {
		Form form("form A", false, 75, 60);
		std::cout << form << std::endl;
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	try {
		Form form("form B", false, 0, 60);
		std::cout << form << std::endl;
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	try {
		Form form("form C", false, 75, 0);
		std::cout << form << std::endl;
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	try {
		Form form("form D", false, 160, 60);
		std::cout << form << std::endl;
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	try {
		Form form("form E", false, 75, 152);
		std::cout << form << std::endl;
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}

	std::cout << std::endl;
	Bureaucrat bureaucrat("bureaucrat A", 76);
	Form form("form F", false, 75, 70);
	std::cout << bureaucrat << std::endl;
	std::cout << form << std::endl;

	bureaucrat.signForm(form);

	bureaucrat.increseGrade();
	std::cout << bureaucrat << std::endl;

	bureaucrat.signForm(form);
	std::cout << bureaucrat << std::endl;
	std::cout << form << std::endl;
	return 0;
}
