
#include "MateriaSource.hpp"

MateriaSource::MateriaSource() {
	std::cout << "MateriaSource default constructor is called" << std::endl;
}

MateriaSource::MateriaSource(const MateriaSource &materiasource) {
	std::cout << "MateriaSource copy constructor is called" << std::endl;
	if (this != &materiasource) {
		for (int i = 0; i < 4; i++) {
			delete knowMaterias[i];
			if (materiasource.knowMaterias[i] == NULL)
				continue;
			knowMaterias[i] = materiasource.knowMaterias[i]->clone();
		}
	}
}

MateriaSource::~MateriaSource() {
	std::cout << "MateriaSource destructor is called" << std::endl;
	for (int i = 0; i < 4; i++)
		delete knowMaterias[i];
}

MateriaSource& MateriaSource::operator=(const MateriaSource &materiasource) {
	std::cout << "MateriaSource copy assignment operator is called" << std::endl;
	if (this != &materiasource) {
		for (int i = 0; i < 4; i++) {
			delete knowMaterias[i];
			if (materiasource.knowMaterias[i] == NULL)
				continue;
			knowMaterias[i] = materiasource.knowMaterias[i]->clone();
		}
	}
	return *this;
}


void MateriaSource::learnMateria(AMateria* m) {
	for (int i = 0; i < 4; i++) {
		if (knowMaterias[i] == NULL) {
			knowMaterias[i] = m;
			return;
		}
		if (knowMaterias[i]->getType() == m->getType()) {
			std::cout << m->getType() << " is already exist type of Materia" << std::endl;
			return;
		}
	}
	std::cout << "There is no more space for this Materia" << std::endl;
}

AMateria* MateriaSource::createMateria(std::string const & type) {
	for (int i = 0; i < 4; i++) {
		if (knowMaterias[i]->getType() == type) {
			return knowMaterias[i]->clone();
		}
	}
	return 0;
}
