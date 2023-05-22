
#pragma once
#include <iostream>
#include <string>

class Animal {
	protected:
		std::string type;

	public:
		Animal();
		Animal(const Animal &animal);
		virtual ~Animal();
		Animal& operator=(const Animal &animal);

		virtual std::string getType() const;
		virtual void makeSound() const;
};
