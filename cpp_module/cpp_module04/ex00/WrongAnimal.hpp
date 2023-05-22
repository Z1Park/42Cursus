
#pragma once
#include <iostream>

class WrongAnimal {
	protected:
		std::string type;

	public:
		WrongAnimal();
		WrongAnimal(const WrongAnimal &animal);
		~WrongAnimal();
		WrongAnimal& operator=(const WrongAnimal &animal);

		virtual std::string getType() const;
		virtual void makeSound() const;
};
