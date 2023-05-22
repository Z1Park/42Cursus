
#include "Contact.hpp"

Contact::Contact(void) : darkest_secret(""), first_name(""), last_name(""), nickname(""), phone_number("") {
}

Contact::Contact(std::string f_name, std::string l_name, std::string nick, std::string phone_num, std::string secret)
	: darkest_secret(secret), first_name(f_name), last_name(l_name), nickname(nick), phone_number(phone_num) {
}

Contact::~Contact(void) {
	darkest_secret.clear();
	first_name.clear();
	last_name.clear();
	nickname.clear();
	phone_number.clear();
}


std::string Contact::getDarkestSecret() const {
	return this->darkest_secret;
}

void	Contact::clearDarkestSecret(void) {
	darkest_secret.clear();
}

void	Contact::setDarkestSecret(std::string new_secret) {
	darkest_secret.clear();
	darkest_secret = new_secret;
}

std::string Contact::getFistName() const {
	return this->first_name;
}

void Contact::setFirstName(std::string first_name) {
	this->first_name = first_name;
}

void Contact::clearFistName() {
	this->first_name.clear();
}

std::string Contact::getLastName() const {
	return this->last_name;
}

void Contact::setLastName(std::string last_name) {
	this->last_name = last_name;
}

void Contact::clearLastName() {
	this->last_name.clear();
}

std::string Contact::getNickname() const {
	return this->nickname;
}

void Contact::setNickname(std::string nickname) {
	this->nickname = nickname;
}

void Contact::clearNickname() {
	this->nickname.clear();
}

std::string Contact::getPhoneNumber() const {
	return this->phone_number;
}

void Contact::setPhoneNumber(std::string phone_number) {
	this->phone_number = phone_number;
}

void Contact::clearPhoneNumber() {
	this->phone_number.clear();
}
