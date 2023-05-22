
#include "ScavTrap.hpp"

int main() {
	ScavTrap A("jpark2");
	ClapTrap B("Serena");

	std::cout << A << std::endl;
	std::cout << B << std::endl;

	A.attack(B.getName());
	B.takeDamage(A.getAttackDamage());

	std::cout << A << std::endl;
	std::cout << B << std::endl;

	B.beRepaired(10);

	std::cout << A << std::endl;
	std::cout << B << std::endl;

	B.attack(A.getName());
	A.takeDamage(B.getAttackDamage());

	std::cout << A << std::endl;
	std::cout << B << std::endl;

	A.guardGate();

	return 0;
}
