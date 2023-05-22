
#pragma once
#include "ICharacter.hpp"

class Character : public ICharacter {
	protected:
		std::string name;
		AMateria *inventory[4];

	public:
		Character();
		Character(std::string name);
		Character(const Character &character);
		~Character();
		Character& operator=(const Character &character);

		std::string const & getName() const;
		void equip(AMateria* m);
		void unequip(int idx);
		void use(int idx, ICharacter& target);
};
