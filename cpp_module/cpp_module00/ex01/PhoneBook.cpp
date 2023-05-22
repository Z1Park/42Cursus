
#include <iomanip>
#include "PhoneBook.hpp"

PhoneBook::PhoneBook(void) : contact_count(0), old_index(0) {
}

PhoneBook::~PhoneBook(void) {
	contact_count = 0;
	old_index = 0;
	for (int i = 0; i < 8; ++i)
	{
		contacts[i].clearDarkestSecret();
		contacts[i].clearFistName();
		contacts[i].clearLastName();
		contacts[i].clearNickname();
		contacts[i].clearPhoneNumber();
	}
}

int	PhoneBook::readString(std::string &str, std::string message) const {
	while (1)
	{
		std::cout << message;
		getline(std::cin, str);
		str.erase(0, str.find_first_not_of(" \t\n\r\f\v"));
		if (std::cin.eof())
			return -1;
		if (str == "")
			std::cout << "you can't make contact with empty field" << std::endl;
		else
			break;
	}
	return 0;
}

void	PhoneBook::printColum(const std::string str, bool last) const {
	std::string tmp;

	if (str.length() > 10)
		tmp = str.substr(0, 9) + ".";
	else
		tmp = str;
	std::cout << std::setw(10) << tmp;
	if (!last)
		std::cout << "|";
	else
		std::cout << std::endl;
}

void PhoneBook::printContact(int index) const {
	std::cout << "frist name : " << contacts[index - 1].getFistName() << std::endl;
	std::cout << "last name : " << contacts[index - 1].getLastName() << std::endl;
	std::cout << "nickname : " << contacts[index - 1].getNickname() << std::endl;
	std::cout << "phone number : " << contacts[index - 1].getPhoneNumber() << std::endl;
	std::cout << "darkest secret : " << contacts[index - 1].getDarkestSecret() << std::endl;
	std::cout << std::endl;
}


void	PhoneBook::addContact(void) {
	std::string new_first_name;
	std::string new_last_name;
	std::string new_nickname;
	std::string new_phone_number;
	std::string new_darkest_secret;
	std::cout << "make new contact" << std::endl;
	if (readString(new_first_name, "first name : ") < 0)
		return ;
	if (readString(new_last_name, "last name : ") < 0)
		return ;
	if (readString(new_nickname, "nickname : ") < 0)
		return ;
	if (readString(new_phone_number, "phone number : ") < 0)
		return ;
	if (readString(new_darkest_secret, "darkest secret : ") < 0)
		return ;
	if (contact_count < 8)
	{
		contacts[contact_count].setFirstName(new_first_name);
		contacts[contact_count].setLastName(new_last_name);
		contacts[contact_count].setNickname(new_nickname);
		contacts[contact_count].setPhoneNumber(new_phone_number);
		contacts[contact_count].setDarkestSecret(new_darkest_secret);
		contact_count++;
	}
	else
	{
		std::cout << contacts[old_index].getNickname() << "'s contact is deleted" << std::endl;
		contacts[old_index].setFirstName(new_first_name);
		contacts[old_index].setLastName(new_last_name);
		contacts[old_index].setNickname(new_nickname);
		contacts[old_index].setPhoneNumber(new_phone_number);
		contacts[old_index].setDarkestSecret(new_darkest_secret);
		old_index = (old_index + 1) % 8;
	}
	std::cout << new_nickname << "'s contact is created" << std::endl;
	std::cout << std::endl;
}

void	PhoneBook::addContact(std::string first_name, std::string last_name, \
				std::string nickname, std::string phone_number, std::string darkest_secret) {
	if (contact_count < 8)
	{
		contacts[contact_count].setFirstName(first_name);
		contacts[contact_count].setLastName(last_name);
		contacts[contact_count].setNickname(nickname);
		contacts[contact_count].setPhoneNumber(phone_number);
		contacts[contact_count].setDarkestSecret(darkest_secret);
		contact_count++;
	}
	else
	{
		std::cout << contacts[old_index].getNickname() << "'s contact is deleted" << std::endl;
		contacts[old_index].setFirstName(first_name);
		contacts[old_index].setLastName(last_name);
		contacts[old_index].setNickname(nickname);
		contacts[old_index].setPhoneNumber(phone_number);
		contacts[old_index].setDarkestSecret(darkest_secret);
		old_index = (old_index + 1) % 8;
	}
	std::cout << nickname << "'s contact is created" << std::endl;
}

void PhoneBook::search(void) const {
	std::string	input;

	if (contact_count == 0)
	{
		std::cout << "phonebook is empty" << std::endl;
		return ;
	}
	printColum("index", false);
	printColum("first name", false);
	printColum("last name", false);
	printColum("nickname", true);
	std::cout << "===========================================" << std::endl;
	for (int i = 0; i < contact_count; ++i)
	{
		printColum(std::to_string(i + 1), false);
		printColum(contacts[i].getFistName(), false);
		printColum(contacts[i].getLastName(), false);
		printColum(contacts[i].getNickname(), true);
	}
	std::cout << std::endl << "enter index of phonebook : ";
	getline(std::cin, input);
	if (std::cin.eof())
		return ;
	else if (input == "1")
		printContact(1);
	else if (input == "2")
		printContact(2);
	else if (input == "3")
		printContact(3);
	else if (input == "4")
		printContact(4);
	else if (input == "5")
		printContact(5);
	else if (input == "6")
		printContact(6);
	else if (input == "7")
		printContact(7);
	else if (input == "8")
		printContact(8);
	else
		std::cout << "Error: wrong index" << std::endl;
}
