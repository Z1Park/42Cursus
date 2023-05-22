
#ifndef __WEAPON_H__
#define __WEAPON_H__
#include <iostream>
#include <string>

class Weapon {
	private:
		std::string type;

	public:
		Weapon();
		Weapon(std::string type);
		Weapon(const Weapon &weapon);
		~Weapon();
		Weapon operator=(const Weapon &weapon);

		const std::string& getType();
		void setType(std::string type);
};

#endif
