
#pragma once
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

class Intern {
	private:
		/* data */

	public:
		Intern();
		Intern(const Intern& ref);
		~Intern();
		Intern&	operator=(const Intern& ref);

		AForm *makeForm(std::string formName, std::string target);

		class NoFormNameException : public std::exception {
			const char * what() const throw();
		};
};
