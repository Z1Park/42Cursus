
#include "ClapTrap.hpp"

int main() {
	ClapTrap A("ClapTrap");
	ClapTrap B("Serena");

	A.setAttackDamage(5);

	std::cout << A << std::endl;
	std::cout << B << std::endl;

	A.attack(B.getName());
	B.takeDamage(A.getAttackDamage());

	std::cout << A << std::endl;
	std::cout << B << std::endl;

	B.beRepaired(4);
	B.setAttackDamage(3);

	std::cout << A << std::endl;
	std::cout << B << std::endl;

	B.attack(A.getName());
	A.takeDamage(B.getAttackDamage());

	std::cout << A << std::endl;
	std::cout << B << std::endl;

	return 0;
}
