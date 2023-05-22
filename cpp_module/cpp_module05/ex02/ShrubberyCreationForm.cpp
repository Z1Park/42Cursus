
#include <fstream>
#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm()
	: AForm("shrubbery", false, 145, 137) {
	std::cout << "ShurbberyCreationForm default constructor is called" << std::endl;
	target = "shrubbery_target";
}

ShrubberyCreationForm::ShrubberyCreationForm(std::string target)
	: AForm("shrubbery form", false, 145, 137) {
	std::cout << "ShurbberyCreationForm parameter constructor is called" << std::endl;
	this->target = target;
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& ref)
	: AForm(ref) {
	std::cout << "ShurbberyCreationForm copy constructor is called" << std::endl;
	this->target = ref.target;
}

ShrubberyCreationForm::~ShrubberyCreationForm() {
	std::cout << "ShurbberyCreationForm destructor is called" << std::endl;
}

ShrubberyCreationForm&	ShrubberyCreationForm::operator=(const ShrubberyCreationForm& ref) {
	std::cout << "ShurbberyCreationForm copy assignment operator is called" << std::endl;
	this->target = ref.target;
	return *this;
}


void ShrubberyCreationForm::execute(Bureaucrat const &executor) const {
	int executor_grade = executor.getGrade();
	std::ofstream out_file;

	if (!AForm::getIsSigned())
		throw AForm::FormIsNotSignedExcpetion();
	if (executor_grade > AForm::getExecuteGrade())
		throw AForm::GradeTooLowException();

	out_file.open(target + "_shrubbery");
	if (out_file.fail()) {
		std::cout << "Can't open " << target << "_shrubbery file" << std::endl;
		return;
	}
	out_file <<
		"                                                         .\n" <<
		"                                              .         ;  \n" <<
		"                 .              .              ;%     ;;   \n" <<
		"                   ,           ,                :;%  %;   \n" <<
		"                    :         ;                   :;%;'     .,   \n" <<
		"           ,.        %;     %;            ;        %;'    ,;\n" <<
		"             ;       ;%;  %%;        ,     %;    ;%;    ,%'\n" <<
		"              %;       %;%;      ,  ;       %;  ;%;   ,%;' \n" <<
		"               ;%;      %;        ;%;        % ;%;  ,%;'\n" <<
		"                `%;.     ;%;     %;'         `;%%;.%;'\n" <<
		"                 `:;%.    ;%%. %@;        %; ;@%;%'\n" <<
		"                    `:%;.  :;bd%;          %;@%;'\n" <<
		"                      `@%:.  :;%.         ;@@%;'   \n" <<
		"                        `@%.  `;@%.      ;@@%;         \n" <<
		"                          `@%%. `@%%    ;@@%;        \n" <<
		"                            ;@%. :@%%  %@@%;       \n" <<
		"                              %@bd%%%bd%%:;     \n" <<
		"                                #@%%%%%:;;\n" <<
		"                                %@@%%%::;\n" <<
		"                                %@@@%(o);  . '         \n" <<
		"                                %@@@o%;:(.,'         \n" <<
		"                            `.. %@@@o%::;         \n" <<
		"                               `)@@@o%::;         \n" <<
		"                                %@@(o)::;        \n" <<
		"                               .%@@@@%::;         \n" <<
		"                               ;%@@@@%::;.          \n" <<
		"                              ;%@@@@%%:;;;. \n" <<
		"                          ...;%@@@@@%%:;;;;,.." << std::endl;
	out_file.close();
	std::cout << "ASCII tree is planted at " << target << "_shrubbery" << std::endl;
}
