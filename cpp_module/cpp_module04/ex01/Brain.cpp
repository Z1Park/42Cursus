
#include "Brain.hpp"

Brain::Brain() {
	std::cout << "Brain default constructor is called" << std::endl;
	for (int i = 0; i < 100; i++) {
		if (i == 0)
			this->ideas[i] = "0";
		else {
			int tmp = 1;
			while (i / tmp != 0)
				tmp *= 10;
			while (tmp / 10 != 0) {
				this->ideas[i] += i * 10 / tmp - i / tmp * 10 + '0';
				tmp /= 10;
			}
		}
		this->ideas[i] += " idea";
	}
}

Brain::Brain(const Brain &brain) {
	std::cout << "Brain copy constructor is called" << std::endl;
	for (int i = 0; i < 100; i++) {
		this->ideas[i] = brain.ideas[i];
	}
}

Brain::~Brain() {
	std::cout << "Brain destructor is called" << std::endl;
}

Brain& Brain::operator=(const Brain &brain) {
	std::cout << "Brain copy assignment operator is called" << std::endl;
	for (int i = 0; i < 100; i++) {
		this->ideas[i] = brain.ideas[i];
	}
	return *this;
}


std::string Brain::getIdea(int index) {
	return this->ideas[index];
}
