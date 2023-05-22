
#pragma once
#include "WrongAnimal.hpp"

class WrongCat : public WrongAnimal {
	public:
		WrongCat();
		WrongCat(const WrongCat &cat);
		~WrongCat();
		WrongCat& operator=(const WrongCat &cat);

		std::string getType() const;
		void makeSound() const;
};
