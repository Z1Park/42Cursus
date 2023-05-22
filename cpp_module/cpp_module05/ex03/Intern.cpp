
#include "Intern.hpp"

Intern::Intern() {
	std::cout << "Intern default constructor is called" << std::endl;
}

Intern::Intern(__attribute__((unused)) const Intern& ref) {
	std::cout << "Intern copy constructor is called" << std::endl;
}

Intern::~Intern() {
	std::cout << "Intern destructor is called" << std::endl;
}

Intern&	Intern::operator=(__attribute__((unused))const Intern& ref) {
	std::cout << "Intern copy assignment operator is called" << std::endl;
	return *this;
}


AForm *Intern::makeForm(std::string formName, std::string target) {
	const std::string forms[] = \
		{"shrubbery creation", "robotomy request", "presidential pardon"};
	int i = 0;
	AForm *form;

	while (i < 3) {
		if (formName == forms[i])
			break;
		i++;
	}
	switch (i)
	{
		case 0:
			form = new ShrubberyCreationForm(target);
			break;
		case 1:
			form = new RobotomyRequestForm(target);
			break;
		case 2:
			form = new PresidentialPardonForm(target);
			break;
		default:
			throw NoFormNameException();
			break;
	}
	std::cout << "Intern creates " << formName << std::endl;
	return form;
}


const char * Intern::NoFormNameException::what() const throw() {
	return "No form name or matched form name to make a form";
}
