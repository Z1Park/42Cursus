
#include "ScavTrap.hpp"

ScavTrap::ScavTrap() : ClapTrap() {
	std::cout << "ScavTrap default constructor is called" << std::endl;
	this->hitPoints = 100;
	this->energyPoints = 50;
	this->attackDamage = 20;
}

ScavTrap::ScavTrap(std::string name) : ClapTrap(name) {
	std::cout << "ScavTrap " << name << " constructor is called" << std::endl;
	this->hitPoints = 100;
	this->energyPoints = 50;
	this->attackDamage = 20;
}

ScavTrap::ScavTrap(const ScavTrap &scavtrap) {
	std::cout << "ScavTrap copy constructor is called" << std::endl;
	this->name = scavtrap.name;
	this->hitPoints = scavtrap.hitPoints;
	this->energyPoints = scavtrap.energyPoints;
	this->attackDamage = scavtrap.attackDamage;
}

ScavTrap::~ScavTrap() {
	std::cout << "ScavTrap destructor is called" << std::endl;
}

ScavTrap& ScavTrap::operator=(const ScavTrap &scavtrap) {
	std::cout << "ScavTrap operator assignment is called" << std::endl;
	this->name = scavtrap.name;
	this->hitPoints = scavtrap.hitPoints;
	this->energyPoints = scavtrap.energyPoints;
	this->attackDamage = scavtrap.attackDamage;
	return *this;
}


void ScavTrap::attack(const std::string &target) {
	if (energyPoints > 0 && hitPoints > 0) {
		energyPoints--;
		std::cout << "ScavTrap " << name << " attacks " << target
			<< ", causing " << attackDamage << " points of damage!" << std::endl;
	}
	else
		std::cout << "No energy or hit points to attack" << std::endl;
}

void ScavTrap::guardGate() {
	if (energyPoints > 0 && hitPoints > 0) {
		energyPoints--;
		std::cout << "ScavTrap " << name << " is now in gatekeeper mode" << std::endl;
	}
	else
		std::cout << "No energy or hit points to gurad gate" << std::endl;
}
