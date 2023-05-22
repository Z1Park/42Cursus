
#include "AMateria.hpp"

class Cure : public AMateria {
	public:
		Cure();
		Cure(std::string const & type);
		Cure(const Cure &cure);
		~Cure();
		Cure& operator=(const Cure &cure);

		std::string const & getType() const;
		Cure* clone() const;
		void use(ICharacter& target);
};
