
#include "Character.hpp"

Character::Character() : name("default") {
	std::cout << "Character default constructor is called" << std::endl;
	for (int i = 0; i < 4; i++)
		inventory[i] = NULL;
}

Character::Character(std::string name) : name(name) {
	std::cout << "Character argument constructor is called" << std::endl;
	for (int i = 0; i < 4; i++)
		inventory[i] = NULL;
}

Character::Character(const Character &character) {
	std::cout << "Character copy constructor is called" << std::endl;
	if (this != &character) {
		this->name = character.name;
		for (int i = 0; i < 4; i++) {
			delete this->inventory[i];
			if (character.inventory[i] == NULL)
				this->inventory[i] = NULL;
			else
				this->inventory[i] = character.inventory[i]->clone();
		}
	}
}

Character::~Character() {
	std::cout << "Character destructor is called" << std::endl;
}

Character& Character::operator=(const Character &character) {
	std::cout << "Character copy assignment operator is called" << std::endl;
	if (this != &character) {
		this->name = character.name;
		for (int i = 0; i < 4; i++) {
			delete this->inventory[i];
			if (character.inventory[i] == NULL)
				this->inventory[i] = NULL;
			else
				this->inventory[i] = character.inventory[i]->clone();
		}
	}
	return *this;
}


std::string const & Character::getName() const {
	return this->name;
}

void Character::equip(AMateria* m) {
	int i = 0;
	while (i < 4) {
		if (inventory[i] == NULL)
			break;
		i++;
	}
	if (i < 4)
		inventory[i] = m;
	else
		std::cout << "Inventory is full" << std::endl;
}

void Character::unequip(int idx) {
	if (inventory[idx] == NULL)
		std::cout << "The " << idx << " inventory is empty" << std::endl;
	else {
		std::cout << "unequip " << inventory[idx]->getType() << " Materia" << std::endl;
		inventory[idx] = NULL;
	}
}

void Character::use(int idx, ICharacter& target) {
	if (inventory[idx] == NULL)
		std::cout << "The " << idx << " inventory is empty" << std::endl;
	else
		inventory[idx]->use(target);
}

