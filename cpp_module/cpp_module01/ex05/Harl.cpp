
#include "Harl.hpp"

void Harl::debug() {
	std::cout << "[ DEBUG ]" << std:: endl;
	std::cout << "I love having extra bacon for my 7XL-double-cheese-triple"
		<< "-pickle-specialketchup burger." << std::endl;
	std::cout << "I really do!" << std::endl << std::endl;
}

void Harl::info() {
	std::cout << "[ INFO ]" << std:: endl;
	std::cout << "I cannot believe adding extra bacon costs more money." << std::endl;
	std::cout << "You didn't put enough bacon in my burger!" << std::endl;
	std::cout << "If you did, I wouldn't be asking for more!" << std::endl << std::endl;
}

void Harl::warning() {
	std::cout << "[ WARNING ]" << std:: endl;
	std::cout << "I think I deserve to have some extra bacon for free." << std::endl;
	std::cout << "I've been coming for years whereas you started "
		<< "working here since last month." << std::endl << std::endl;
}

void Harl::error() {
	std::cout << "[ ERROR ]" << std:: endl;
	std::cout << "This is unacceptable! "
		<< "I want to speak to the manager now." << std::endl << std::endl;
}


void Harl::complain(std::string level) {
	void (*const harl_func[4])(void) = \
		{Harl::debug, Harl::info, Harl::warning, Harl::error};
	const std::string identifier[8] = {"debug", "info", "warning", "error", \
		"DEBUG", "INFO", "WARNING", "ERROR"};

	for (int i = 0; i < 4; i++) {
		if (level == identifier[i] || level == identifier[i + 4]) {
			harl_func[i]();
			break;
		}
	}
}
