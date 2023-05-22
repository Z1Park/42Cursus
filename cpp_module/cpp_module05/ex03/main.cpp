
#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"

int main() {
	Intern someRandomIntern;
	AForm *form;

	try {
		form = someRandomIntern.makeForm("shrubbery creation", "Ader");
		delete form;
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	try {
		form = someRandomIntern.makeForm("robotomy request", "Bender");
		delete form;
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	try {
		form = someRandomIntern.makeForm("presidential pardon", "Cixel");
		delete form;
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	try {
		form = someRandomIntern.makeForm("nothing match form", "Damond");
		delete form;
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	try {
		form = someRandomIntern.makeForm("", "Echo");
		delete form;
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
