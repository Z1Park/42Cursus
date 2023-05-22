
#pragma once
#include "Animal.hpp"
#include "Brain.hpp"

class Dog : public Animal {
	private:
		Brain *brain;

	public:
		Dog();
		Dog(const Dog &dog);
		~Dog();
		Dog& operator=(const Dog &dog);

		std::string getType() const;
		void makeSound() const;
		Brain *getBrain() const;
};
