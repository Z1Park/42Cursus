
#ifndef __CONTACT_H__
#define __CONTACT_H__
#include <iostream>

class Contact {
	private:
		std::string darkest_secret;
		std::string first_name;
		std::string last_name;
		std::string nickname;
		std::string phone_number;

	public:
		Contact(void);
		Contact(std::string f_name, std::string l_name, std::string nick, std::string phone_num, std::string secret);
		~Contact(void);

		std::string getDarkestSecret() const;
		void setDarkestSecret(std::string new_secret);
		void clearDarkestSecret(void);
		std::string getFistName() const;
		void setFirstName(std::string first_name);
		void clearFistName();
		std::string getLastName() const;
		void setLastName(std::string last_name);
		void clearLastName();
		std::string getNickname() const;
		void setNickname(std::string nickname);
		void clearNickname();
		std::string getPhoneNumber() const;
		void setPhoneNumber(std::string phone_number);
		void clearPhoneNumber();
};

#endif /* __CONTACT_H__ */
