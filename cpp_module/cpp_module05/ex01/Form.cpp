
#include "Form.hpp"

Form::Form() : name("default"), isSigned(false), signGrade(150), executeGrade(150) {
	std::cout << "Form default constructor is called" << std::endl;
}

Form::Form(std::string name, bool isSigned, const int signGrade, const int executeGrade)
	: name(name), isSigned(isSigned), signGrade(signGrade), executeGrade(executeGrade) {
	std::cout << "Form argument constructor is called" << std::endl;
	if (signGrade < 1)
		throw GradeTooHighException();
	else if (signGrade > 150)
		throw GradeTooLowException();
	if (executeGrade < 1)
		throw GradeTooHighException();
	else if (executeGrade > 150)
		throw GradeTooLowException();
}

Form::Form(const Form &form)
	: name(form.name), isSigned(form.isSigned),
	signGrade(form.signGrade), executeGrade(form.executeGrade)  {
	std::cout << "Form copy constructor is called" << std::endl;
}

Form::~Form() {
	std::cout << "Form destructor is called" << std::endl;
}

Form& Form::operator=(const Form &form) {
	std::cout << "Bureaucrat copy assignment operator is called" << std::endl;
	this->isSigned = form.isSigned;
	return *this;
}


std::string Form::getName() {
	return name;
}

bool Form::getIsSigned() {
	return isSigned;
}

int Form::getSignGrade() {
	return signGrade;
}

int Form::getExecuteGrade() {
	return executeGrade;
}

void Form::beSigned(Bureaucrat &bureaucrat) {
	if (isSigned) {
		std::cout << "The form " << name << " is already signed" << std::endl;
		return;
	}
	if (bureaucrat.getGrade() <= signGrade)
		isSigned = true;
	else
		throw GradeTooLowException();
}



const char * Form::GradeTooHighException::what() const throw() {
	return "Grade is too high";
}

const char * Form::GradeTooLowException::what() const throw() {
	return "Grade is too low";
}


std::ostream& operator<<(std::ostream &os, Form &form) {
	os << "Form name : " << form.getName() << ", is signed : "
		<< form.getIsSigned() << ", required grade to sign : "
		<< form.getSignGrade() << ", required grade to execute : "
		<< form.getExecuteGrade();
	return os;
}

