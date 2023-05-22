
#pragma once
#include <iostream>
#include <string>

class Brain {
	private:
		std::string ideas[100];

	public:
		Brain();
		Brain(const Brain &brain);
		~Brain();
		Brain& operator=(const Brain &brain);

		std::string getIdea(int index);
};
