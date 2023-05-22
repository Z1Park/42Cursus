
#pragma once
#include <iostream>
#include <string>
#include <exception>
#include "Bureaucrat.hpp"

class Bureaucrat;

class Form {
	private:
		const std::string name;
		bool isSigned;
		const int signGrade;
		const int executeGrade;

	public:
		Form();
		Form(std::string name, bool isSigned, const int signGrade, const int executeGrade);
		Form(const Form &form);
		~Form();
		Form& operator=(const Form &form);

		std::string getName();
		bool getIsSigned();
		int getSignGrade();
		int getExecuteGrade();
		void beSigned(Bureaucrat &bureaucrat);

		class GradeTooHighException : public std::exception {
			const char * what() const throw();
		};
		class GradeTooLowException : public std::exception {
			const char * what() const throw();
		};
};

std::ostream& operator<<(std::ostream &os, Form &form);
