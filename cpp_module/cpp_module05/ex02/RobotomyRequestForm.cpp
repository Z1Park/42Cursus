
#include <cstdlib>
#include <ctime>
#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm()
	: AForm("default", false, 72, 45) {
	std::cout << "RobotomyRequestForm default constructor is called" << std::endl;
	this->target = "robotomize_target";
}

RobotomyRequestForm::RobotomyRequestForm(std::string target)
	: AForm("robotomize form", false, 72, 45) {
	std::cout << "RobotomyRequestForm parameter constructor is called" << std::endl;
	this->target = target;
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& ref)
	: AForm(ref) {
	std::cout << "RobotomyRequestForm copy constructor is called" << std::endl;
	this->target = ref.target;
}

RobotomyRequestForm::~RobotomyRequestForm() {
	std::cout << "RobotomyRequestForm destructor is called" << std::endl;
}

RobotomyRequestForm&	RobotomyRequestForm::operator=(const RobotomyRequestForm& ref) {
	std::cout << "RobotomyRequestForm copy assignment operator is called" << std::endl;
	this->target = ref.target;
	return *this;
}

void RobotomyRequestForm::execute(Bureaucrat const &executor) const {
	int executor_grade = executor.getGrade();
	int random;

	if (!AForm::getIsSigned())
		throw AForm::FormIsNotSignedExcpetion();
	if (executor_grade > AForm::getExecuteGrade())
		throw AForm::GradeTooLowException();

	std::srand(std::time(NULL));
	random = std::rand() % 2;
	std::cout << "* Drrrrrrrr... *" << std::endl;
	if (random == 0)
		std::cout << target << " has been robotomized success" << std::endl;
	else
		std::cout << target << " has been robotomized fail" << std::endl;
}
