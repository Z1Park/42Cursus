
#pragma once
#include "Animal.hpp"

class Dog : public Animal {
	public:
		Dog();
		Dog(const Dog &dog);
		~Dog();
		Dog& operator=(const Dog &dog);

		std::string getType() const;
		void makeSound() const;
};
