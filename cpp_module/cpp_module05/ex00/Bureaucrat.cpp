
#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat() : name("default"), grade(150) {
	std::cout << "Bureaucrat default constructor is called" << std::endl;
}

Bureaucrat::Bureaucrat(std::string name, int grade) : name(name) {
	std::cout << "Bureaucrat argument constructor is called" << std::endl;
	if (grade < 1)
		throw Bureaucrat::GradeTooHighException();
	else if (grade > 150)
		throw Bureaucrat::GradeTooLowException();
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
	this->grade = bureaucrat.grade;
	return *this;
}


std::string Bureaucrat::getName() const {
	return name;
}

int Bureaucrat::getGrade() const {
	return grade;
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
