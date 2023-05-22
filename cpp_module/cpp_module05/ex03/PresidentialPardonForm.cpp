
#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm()
	: AForm("default", false, 25, 5) {
	std::cout << "PresidentialPardonForm default constructor is called" << std::endl;
	this->target = "presidential_target";
}

PresidentialPardonForm::PresidentialPardonForm(std::string target)
	: AForm("presidential pardon form", false, 25, 5) {
	std::cout << "PresidentialPardonForm parameter constructor is called" << std::endl;
	this->target = target;
}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm& ref) : AForm(ref) {
	std::cout << "PresidentialPardonForm copy constructor is called" << std::endl;
	this->target = ref.target;
}

PresidentialPardonForm::~PresidentialPardonForm() {
	std::cout << "PresidentialPardonForm destructor is called" << std::endl;
}

PresidentialPardonForm&	PresidentialPardonForm::operator=(const PresidentialPardonForm& ref) {
	std::cout << "PresidentialPardonForm copy assignment operator is called" << std::endl;
	this->target = ref.target;
	return (*this);
}

void PresidentialPardonForm::execute(Bureaucrat const &executor) const {
	int executor_grade = executor.getGrade();

	if (!AForm::getIsSigned())
		throw AForm::FormIsNotSignedExcpetion();
	if (executor_grade > AForm::getExecuteGrade())
		throw AForm::GradeTooLowException();

	std::cout << target << " has been pardoned by Zaphod Beeblebrox" << std::endl;
}
