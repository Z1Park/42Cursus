
#pragma once
#include "ClapTrap.hpp"

class ScavTrap : public ClapTrap {
	public:
		ScavTrap();
		ScavTrap(std::string name);
		ScavTrap(const ScavTrap &scavtrap);
		~ScavTrap();
		ScavTrap& operator=(const ScavTrap &scavtrap);

		void attack(const std::string &target);
		void guardGate();
};
