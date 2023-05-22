
#include "AMateria.hpp"

class Ice : public AMateria {
	public:
		Ice();
		Ice(std::string const & type);
		Ice(const Ice &ice);
		~Ice();
		Ice& operator=(const Ice &ice);

		std::string const & getType() const;
		Ice* clone() const;
		void use(ICharacter& target);
};
