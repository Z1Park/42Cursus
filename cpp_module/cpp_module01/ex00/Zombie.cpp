
#include "Zombie.hpp"

Zombie::Zombie(std::string new_name) : name(new_name) {
	std::cout << "zombie " << name << " is born" << std::endl;
}

Zombie::~Zombie() {
	std::cout << "zombie " << name << " die" << std::endl;
	name.clear();
}

void	Zombie::announce() {
	std::cout << name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

Zombie	*newZombie(std::string name) {
	Zombie	*new_zombie = new Zombie(name);
	return (new_zombie);
}

void	randomChump(std::string name) {
	Zombie new_zombie(name);
	new_zombie.announce();
}
