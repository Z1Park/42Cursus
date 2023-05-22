
#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat() : name("default"), grade(150) {
	std::cout << "Bureaucrat default constructor is called" << std::endl;
}

Bureaucrat::Bureaucrat(std::string name, int grade) : name(name) {
	std::cout << "Bureaucrat argument constructor is called" << std::endl;
	if (grade < 1) {
		grade = 1;
		throw Bureaucrat::GradeTooHighException();
	}
	else if (grade > 150) {
		grade = 150;
		throw Bureaucrat::GradeTooLowException();
	}
	else
		this->grade = grade;
}

Bureaucrat::Bureaucrat(const Bureaucrat &bureaucrat) : name(bureaucrat.name), grade(bureaucrat.grade) {
	std::cout << "Bureaucrat copy constructor is called" << std::endl;
}

Bureaucrat::~Bureaucrat() {
	std::cout << "Bureaucrat destructor is called" << std::endl;
}

Bureaucrat& Bureaucrat::operator=(const Bureaucrat &bureaucrat) {
	std::cout << "Bureaucrat copy assignment operator is called" << std::endl;
	if (this != &bureaucrat)
		this->grade = bureaucrat.grade;
	return *this;
}


std::string Bureaucrat::getName() const {
	return this->name;
}

int Bureaucrat::getGrade() const {
	return this->grade;
}

void Bureaucrat::increseGrade() {
	if (grade <= 1)
		throw Bureaucrat::GradeTooHighException();
	else
		grade--;
}

void Bureaucrat::decreseGrade() {
	if (grade >= 150)
		throw Bureaucrat::GradeTooLowException();
	else
		grade++;
}

void Bureaucrat::signForm(AForm &form) {
	try {
		form.beSigned(*this);
		std::cout << name << " signed " << form.getName() << std::endl;
	} catch (std::exception &e) {
		std::cerr << name << " couldn't sign " << form.getName()
			<< " because " << e.what() << std::endl;
	}
}

void Bureaucrat::executeForm(AForm const &form) {
	try {
		form.execute(*this);
		std::cout << name << " executed " << form.getName() << std::endl;
	} catch (std::exception &e) {
		std::cerr << name << " couldn't execute " << form.getName()
			<< " because " << e.what() << std::endl;
	}
}


const char * Bureaucrat::GradeTooHighException::what() const throw() {
	return "Grade is Too high.";
}

const char * Bureaucrat::GradeTooLowException::what() const throw() {
	return "Grade is Too low.";
}

std::ostream& operator<<(std::ostream &os, Bureaucrat &bureaucrat) {
	os << bureaucrat.getName() << ", bureaucrat grade " << bureaucrat.getGrade() << ".";
	return os;
}
