
#include "AForm.hpp"

AForm::AForm() : name("default"), isSigned(false), signGrade(150), executeGrade(150) {
	std::cout << "AForm default constructor is called" << std::endl;
}

AForm::AForm(std::string name, bool isSigned, const int signGrade, const int executeGrade)
	: name(name), isSigned(isSigned), signGrade(signGrade), executeGrade(executeGrade) {
	std::cout << "AForm argument constructor is called" << std::endl;
	if (signGrade < 1)
		throw GradeTooHighException();
	else if (signGrade > 150)
		throw GradeTooLowException();
	if (executeGrade < 1)
		throw GradeTooHighException();
	else if (executeGrade > 150)
		throw GradeTooLowException();
}

AForm::AForm(const AForm &form)
	: name(form.name), isSigned(form.isSigned),
	signGrade(form.signGrade), executeGrade(form.executeGrade)  {
	std::cout << "AForm copy constructor is called" << std::endl;
}

AForm::~AForm() {
	std::cout << "AForm destructor is called" << std::endl;
}

AForm& AForm::operator=(const AForm &form) {
	std::cout << "Bureaucrat copy assignment operator is called" << std::endl;
	this->isSigned = form.isSigned;
	return *this;
}


std::string AForm::getName() const {
	return name;
}

bool AForm::getIsSigned() const {
	return isSigned;
}

int AForm::getSignGrade() const {
	return signGrade;
}

int AForm::getExecuteGrade() const {
	return executeGrade;
}

void AForm::beSigned(Bureaucrat &bureaucrat) {
	if (isSigned) {
		std::cout << "The Aform " << name << " is already signed" << std::endl;
		return;
	}
	if (bureaucrat.getGrade() <= signGrade)
		isSigned = true;
	else
		throw GradeTooLowException();
}



const char * AForm::GradeTooHighException::what() const throw() {
	return "Grade is too high";
}

const char * AForm::GradeTooLowException::what() const throw() {
	return "Grade is too low";
}

const char * AForm::FormIsNotSignedExcpetion::what() const throw() {
	return "The form is not signed";
}


std::ostream& operator<<(std::ostream &os, AForm &Aform) {
	os << "AForm name : " << Aform.getName() << ", is signed : "
		<< Aform.getIsSigned() << ", required grade to sign : "
		<< Aform.getSignGrade() << ", required grade to execute : "
		<< Aform.getExecuteGrade();
	return os;
}

