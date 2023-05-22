
#pragma once
#include "Animal.hpp"

class Cat : public Animal {
	public:
		Cat();
		Cat(const Cat &cat);
		~Cat();
		Cat& operator=(const Cat &cat);

		std::string getType() const;
		void makeSound() const;
};
