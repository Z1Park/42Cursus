
#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main() {
	Bureaucrat A("a", 140);
	Bureaucrat B("b", 70);
	Bureaucrat C("c", 20);
	Bureaucrat D("d", 1);
	ShrubberyCreationForm shu_form("home");
	RobotomyRequestForm robo_form("steve");
	PresidentialPardonForm pres_form("james");
	std::cout << std::endl;

	std::cout << "test for execute form which isn't signed" << std::endl;
	try {
		D.executeForm(shu_form);
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	std::cout << std::endl;

	std::cout << "test for sign success and execute fail" << std::endl;
	try {
		A.signForm(shu_form);
		A.executeForm(shu_form);
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	std::cout << std::endl;

	std::cout << "test for shrubbery creation form" << std::endl;
	try {
		B.executeForm(shu_form);
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	std::cout << std::endl;

	std::cout << "test for robotomy reqeust form" << std::endl;
	try {
		C.signForm(robo_form);
		C.executeForm(robo_form);
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
	std::cout << std::endl;

	std::cout << "test for presidential pardon form" << std::endl;
	try {
		D.signForm(pres_form);
		D.executeForm(pres_form);
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
