
#pragma once
#include <iostream>
#include <string>
#include <exception>
#include "Bureaucrat.hpp"

class Bureaucrat;

class AForm {
	private:
		const std::string name;
		bool isSigned;
		const int signGrade;
		const int executeGrade;

	public:
		AForm();
		AForm(std::string name, bool isSigned, const int signGrade, const int executeGrade);
		AForm(const AForm &form);
		virtual ~AForm();
		AForm& operator=(const AForm &form);

		std::string getName() const;
		bool getIsSigned() const;
		int getSignGrade() const;
		int getExecuteGrade() const;
		void beSigned(Bureaucrat &bureaucrat);

		virtual void execute(Bureaucrat const &executor) const = 0;

		class GradeTooHighException : public std::exception {
			const char * what() const throw();
		};
		class GradeTooLowException : public std::exception {
			const char * what() const throw();
		};
		class FormIsNotSignedExcpetion : public std::exception {
			const char * what() const throw();
		};
};

std::ostream& operator<<(std::ostream &os, AForm &form);
