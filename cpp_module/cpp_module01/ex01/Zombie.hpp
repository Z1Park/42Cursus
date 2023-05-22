
#ifndef __ZOMBIE_H__
#define __ZOMBIE_H__
#include <iostream>
#include <string>

class Zombie {
	private:
		std::string name;

	public:
		Zombie();
		Zombie(std::string new_name);
		~Zombie();

		void	setName(std::string name);
		void	announce();
};

Zombie	*newZombie(std::string name);
void	randomChump(std::string name);
Zombie	*zombieHorde(int N, std::string name);

#endif
