
#pragma once
#include "ScavTrap.hpp"
#include "FragTrap.hpp"

class DiamondTrap : public ScavTrap, public FragTrap {
	private:
		std::string name;

	public:
		DiamondTrap();
		DiamondTrap(std::string name);
		DiamondTrap(const DiamondTrap &fragtrap);
		~DiamondTrap();
		DiamondTrap& operator=(const DiamondTrap &fragtrap);

		std::string getName();
		void whoAmI();
};
