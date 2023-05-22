
#pragma once
#include "IMateriaSource.hpp"

class MateriaSource : public IMateriaSource {
	private:
		AMateria *knowMaterias[4];

	public:
		MateriaSource();
		MateriaSource(const MateriaSource &materiasource);
		~MateriaSource();
		MateriaSource& operator=(const MateriaSource &materiasource);

		void learnMateria(AMateria* m);
		AMateria* createMateria(std::string const & type);
};
