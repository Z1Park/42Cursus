
#pragma once
#include <iostream>
#include <string>
#include <exception>

class Bureaucrat {
	private:
		const std::string name;
		int grade;

	public:
		Bureaucrat();
		Bureaucrat(std::string name, int grade);
		Bureaucrat(const Bureaucrat &bureaucrat);
		~Bureaucrat();
		Bureaucrat& operator=(const Bureaucrat &bureaucrat);

		std::string getName() const;
		int getGrade() const;
		void increseGrade();
		void decreseGrade();

		class GradeTooHighException : public std::exception {
			const char * what() const throw();
		};
		class GradeTooLowException : public std::exception {
			const char * what() const throw();
		};
};

std::ostream& operator<<(std::ostream &os, Bureaucrat &bureaucrat);
