
#include "PhoneBook.hpp"

int	main(void)
{
	PhoneBook	phonebook;
	std::string	input;
	std::string	index;

	/* Setting for test------------------ */
	phonebook.addContact("jiwon", "park", "jpark2", "123", "aa");
	phonebook.addContact("mingwan", "kang", "mingkang", "234", "bb");
	phonebook.addContact("seong", "hyun", "seonghyu", "345", "cc");
	phonebook.addContact("sunwoo", "song", "sunwsong", "456", "dd");
	phonebook.addContact("younhwan", "oh", "yooh", "567", "ee");
	phonebook.addContact("junseok", "bok", "jbok", "678", "ff");
	phonebook.addContact("sangje", "an", "sanan", "789", "gg");
	phonebook.addContact("dongwook", "jeong", "dojeong", "890", "hh");
	/* ------------------Setting for test */

	while (1)
	{
		std::cout << "enter command : ";
		getline(std::cin, input);
		if (std::cin.eof())
			break;
		if (input == "ADD" || input == "add")
			phonebook.addContact();
		else if (input == "SEARCH" || input == "search")
			phonebook.search();
		else if (input == "EXIT" || input == "exit")
			break ;
		else
			std::cout << "Error: input is wrong" << std::endl;
	}
	return 0;
}
