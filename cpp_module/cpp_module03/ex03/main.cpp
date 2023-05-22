
#include "ScavTrap.hpp"
#include "FragTrap.hpp"
#include "DiamondTrap.hpp"

int main() {
	ClapTrap A("jpark2");
	ScavTrap B("hihi");
	FragTrap C("Serena");
	DiamondTrap D("Damond");

	A.setAttackDamage(15);

	std::cout << A << std::endl;
	std::cout << B << std::endl;
	std::cout << C << std::endl;
	std::cout << D << std::endl;

	A.attack(C.getName());
	C.takeDamage(A.getAttackDamage());

	std::cout << A << std::endl;
	std::cout << B << std::endl;
	std::cout << C << std::endl;
	std::cout << D << std::endl;

	C.beRepaired(10);
	B.attack(A.getName());
	A.takeDamage(B.getAttackDamage());
	D.attack(B.getName());
	B.takeDamage(D.getAttackDamage());

	std::cout << A << std::endl;
	std::cout << B << std::endl;
	std::cout << C << std::endl;
	std::cout << D << std::endl;

	B.attack(D.getName());
	D.takeDamage(B.getAttackDamage());

	std::cout << A << std::endl;
	std::cout << B << std::endl;
	std::cout << C << std::endl;
	std::cout << D << std::endl;

	B.guardGate();
	C.highFivesGuys();
	D.whoAmI();

	return 0;
}
