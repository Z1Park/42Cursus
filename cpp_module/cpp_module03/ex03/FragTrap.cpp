
#include "FragTrap.hpp"

FragTrap::FragTrap() : ClapTrap() {
	std::cout << "FragTrap default constructor is called" << std::endl;
	this->hitPoints = 100;
	this->energyPoints = 100;
	this->attackDamage = 30;
}

FragTrap::FragTrap(std::string name) : ClapTrap(name) {
	std::cout << "FragTrap " << name << " constructor is called" << std::endl;
	this->hitPoints = 100;
	this->energyPoints = 100;
	this->attackDamage = 30;
}

FragTrap::FragTrap(const FragTrap &fragtrap) {
	std::cout << "FragTrap copy constructor is called" << std::endl;
	this->name = fragtrap.name;
	this->hitPoints = fragtrap.hitPoints;
	this->energyPoints = fragtrap.energyPoints;
	this->attackDamage = fragtrap.attackDamage;
}

FragTrap::~FragTrap() {
	std::cout << "FragTrap destructor is called" << std::endl;
}

FragTrap& FragTrap::operator=(const FragTrap &fragtrap) {
	std::cout << "FragTrap operator assignment is called" << std::endl;
	this->name = fragtrap.name;
	this->hitPoints = fragtrap.hitPoints;
	this->energyPoints = fragtrap.energyPoints;
	this->attackDamage = fragtrap.attackDamage;
	return *this;
}


void FragTrap::highFivesGuys() {
	if (energyPoints > 0 && hitPoints > 0) {
		energyPoints--;
		std::cout << "FragTrap " << name << " requests high fives" << std::endl;
	}
	else
		std::cout << "No energy or hit points to high fives" << std::endl;
}
