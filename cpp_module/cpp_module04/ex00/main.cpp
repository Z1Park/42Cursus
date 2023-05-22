
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongCat.hpp"

int main()
{
	{
		const Animal* meta = new Animal();
		const Animal* j = new Dog();
		const Animal* i = new Cat();
		std::cout << "type of this animal : " << j->getType() << " " << std::endl;
		std::cout << "type of this animal : " << i->getType() << " " << std::endl;
		i->makeSound(); //will output the cat sound!
		j->makeSound(); //will output the dog sound!
		meta->makeSound(); //will output no sound!
	}
	{
		const WrongAnimal* wrong_meta = new WrongAnimal();
		const WrongAnimal* wrong_i = new WrongCat();
		wrong_i->makeSound(); //will output wrong sound!
		wrong_meta->makeSound(); //will output wrong sound!
	}
	return 0;
}
