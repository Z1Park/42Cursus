
#include "Cat.hpp"
#include "Dog.hpp"

int main()
{
	const Animal *animals[20];
	for (int i = 0; i < 20; i++) {
		if (i < 10)
			animals[i] = new Dog();
		else
			animals[i] = new Cat();
	}
	for (int i = 0; i < 20; i++)
		delete animals[i];
	const Cat *cat = new Cat();
	std::cout << cat->getBrain()->getIdea(0) << std::endl;
	std::cout << cat->getBrain()->getIdea(99) << std::endl;
	const Dog *dog = new Dog();
	std::cout << dog->getBrain()->getIdea(0) << std::endl;
	std::cout << dog->getBrain()->getIdea(99) << std::endl;
	delete cat;
	delete dog;
	return 0;
}
