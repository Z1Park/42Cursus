
#pragma once
#include "Animal.hpp"
#include "Brain.hpp"

class Cat : public Animal {
	private:
		Brain *brain;

	public:
		Cat();
		Cat(const Cat &cat);
		~Cat();
		Cat& operator=(const Cat &cat);

		std::string getType() const;
		void makeSound() const;
		Brain *getBrain() const;
};
