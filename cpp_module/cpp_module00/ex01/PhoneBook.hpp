
#ifndef __PHONEBOOK_H__
#define __PHONEBOOK_H__
#include "Contact.hpp"

class PhoneBook {
	private:
		int		contact_count;
		int		old_index;
		Contact	contacts[8];
		int readString(std::string &str, std::string message) const;
		void printColum(const std::string str, bool last) const;
		void printContact(int index) const;

	public:
		PhoneBook(void);
		~PhoneBook(void);

		void addContact(void);
		void addContact(std::string f_name, std::string l_name, std::string nick, \
						std::string phone_num, std::string secret);
		void search(void) const;
};

#endif /* __PHONEBOOK_H__ */
