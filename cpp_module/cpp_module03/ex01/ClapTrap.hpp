
#pragma once
#include <iostream>
#include <string>

class ClapTrap {
	protected:
		std::string name;
		unsigned int hitPoints;
		unsigned int energyPoints;
		unsigned int attackDamage;

	public:
		ClapTrap();
		ClapTrap(std::string name);
		ClapTrap(const ClapTrap &claptrap);
		virtual ~ClapTrap();
		ClapTrap& operator=(const ClapTrap &claptrap);

		std::string getName();
		void setName(std::string name);
		unsigned int getHitPoints();
		void setHitPoints(int hitPoints);
		unsigned int getEnergyPoints();
		void setEnergyPoints(int energyPoints);
		unsigned int getAttackDamage();
		void setAttackDamage(int attackDamage);

		virtual void attack(const std::string &target);
		void takeDamage(unsigned int amount);
		void beRepaired(unsigned int amount);
};

std::ostream& operator<<(std::ostream &os, ClapTrap &claptrap);
