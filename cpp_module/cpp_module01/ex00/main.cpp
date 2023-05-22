
#include "Zombie.hpp"

int	main()
{
	Zombie zombie1("zmb1");
	Zombie *zombie2 = newZombie("zmb2");
	zombie1.announce();
	zombie2->announce();
	randomChump("zmb3");
	delete zombie2;
}
