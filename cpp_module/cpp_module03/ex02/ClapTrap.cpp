
#include "ClapTrap.hpp"

std::ostream& operator<<(std::ostream &os, ClapTrap &claptrap) {
	os << "name : " << claptrap.getName() << std::endl
		<< "attackDamage : " << claptrap.getAttackDamage() << std::endl
		<< "hitPoints : " << claptrap.getHitPoints() << std::endl
		<< "energyPoints : " << claptrap.getEnergyPoints() << std::endl;
	return os;
}

ClapTrap::ClapTrap() : name("default"), hitPoints(10), energyPoints(10), attackDamage(0) {
	std::cout << "ClapTrap default constructor is called" << std::endl;
}

ClapTrap::ClapTrap(std::string name) : name(name), hitPoints(10), energyPoints(10), attackDamage(0) {
	std::cout << "ClapTrap " << name << " constructor is called" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &claptrap) {
	std::cout << "ClapTrap copy constructor is called" << std::endl;
	this->name = claptrap.name;
	this->hitPoints = claptrap.hitPoints;
	this->energyPoints = claptrap.energyPoints;
	this->attackDamage = claptrap.attackDamage;
}

ClapTrap::~ClapTrap() {
	std::cout << "ClapTrap destructor is called" << std::endl;
}

ClapTrap& ClapTrap::operator=(const ClapTrap &claptrap) {
	std::cout << "ClapTrap Operator assignment is called" << std::endl;
	this->name = claptrap.name;
	this->hitPoints = claptrap.hitPoints;
	this->energyPoints = claptrap.energyPoints;
	this->attackDamage = claptrap.attackDamage;
	return *this;
}


std::string ClapTrap::getName() {
	return name;
}

void ClapTrap::setName(std::string name) {
	this->name = name;
}

unsigned int ClapTrap::getHitPoints() {
	return hitPoints;
}

void ClapTrap::setHitPoints(int hitPoints) {
	this->hitPoints = hitPoints;
}

unsigned int ClapTrap::getEnergyPoints() {
	return energyPoints;
}

void ClapTrap::setEnergyPoints(int energyPoints) {
	this->energyPoints = energyPoints;
}

unsigned int ClapTrap::getAttackDamage() {
	return attackDamage;
}

void ClapTrap::setAttackDamage(int attackDamage) {
	this->attackDamage = attackDamage;
}


void ClapTrap::attack(const std::string &target) {
	if (energyPoints > 0 && hitPoints > 0) {
		energyPoints--;
		std::cout << "ClapTrap " << name << " attacks " << target
			<< ", causing " << attackDamage << " points of damage!" << std::endl;
	}
	else
		std::cout << "No energy or hit points to attack" << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount) {
	if (hitPoints < amount) {
		std::cout << "ClapTrap " << name << " takes "
			<< hitPoints << " points of damage!" << std::endl;
		hitPoints = 0;
	}
	else {
		std::cout << name << " takes " \
			<< amount << " points of damage!" << std::endl;
		hitPoints -= amount;
	}
}

void ClapTrap::beRepaired(unsigned int amount) {
	if (energyPoints > 0 && hitPoints > 0) {
		std::cout << "ClapTrap " << name << " is repaired "
			<< amount << " points of hitpoints!" << std::endl;
		energyPoints--;
		hitPoints += amount;
	}
	else
		std::cout << "No energy or hit points to attack" << std::endl;
}
