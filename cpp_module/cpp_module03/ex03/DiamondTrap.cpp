
#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap() : ClapTrap(), ScavTrap(), FragTrap() {
	std::cout << "DiamondTrap default constructor is called" << std::endl;
	ClapTrap::name = name + "_clap_name";
	this->energyPoints = 50;
}

DiamondTrap::DiamondTrap(std::string name) : ClapTrap(), ScavTrap(), FragTrap() {
	std::cout << "DiamondTrap " << name << " constructor is called" << std::endl;
	ClapTrap::name = name + "_clap_name";
	this->name = name;
	this->energyPoints = 50;
}

DiamondTrap::DiamondTrap(const DiamondTrap &diamondtrap) {
	std::cout << "DiamondTrap Copy constructor is called" << std::endl;
	this->name = diamondtrap.name;
	this->hitPoints = diamondtrap.hitPoints;
	this->energyPoints = diamondtrap.energyPoints;
	this->attackDamage = diamondtrap.attackDamage;
}

DiamondTrap::~DiamondTrap() {
	std::cout << "DiamondTrap destructor is called" << std::endl;
}

DiamondTrap& DiamondTrap::operator=(const DiamondTrap &diamondtrap) {
	std::cout << "DiamondTrap Operator assignment is called" << std::endl;
	this->name = diamondtrap.name;
	this->hitPoints = diamondtrap.hitPoints;
	this->energyPoints = diamondtrap.energyPoints;
	this->attackDamage = diamondtrap.attackDamage;
	return *this;
}


std::string DiamondTrap::getName() {
	return this->name;
}

void DiamondTrap::whoAmI() {
	std::cout << "ClapTrap name : " << ClapTrap::name << std::endl;
	std::cout << "name : " << name << std::endl;
}
