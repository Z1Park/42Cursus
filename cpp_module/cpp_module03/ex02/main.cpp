
#include "ScavTrap.hpp"
#include "FragTrap.hpp"

int main() {
	ClapTrap A("jpark2");
	ScavTrap B("hihi");
	FragTrap C("Serena");

	A.setAttackDamage(15);

	std::cout << A << std::endl;
	std::cout << B << std::endl;
	std::cout << C << std::endl;

	A.attack(C.getName());
	C.takeDamage(A.getAttackDamage());

	std::cout << A << std::endl;
	std::cout << B << std::endl;
	std::cout << C << std::endl;

	C.beRepaired(10);
	B.attack(A.getName());
	A.takeDamage(B.getAttackDamage());

	std::cout << A << std::endl;
	std::cout << B << std::endl;
	std::cout << C << std::endl;

	B.attack(A.getName());
	A.takeDamage(B.getAttackDamage());

	std::cout << A << std::endl;
	std::cout << B << std::endl;
	std::cout << C << std::endl;

	B.guardGate();
	C.highFivesGuys();

	return 0;
}
