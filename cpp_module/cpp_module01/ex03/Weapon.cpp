
#include "Weapon.hpp"

Weapon::Weapon() {
}

Weapon::Weapon(std::string type) : type(type) {
}

Weapon::Weapon(const Weapon &weapon) {
	type = weapon.type;
}

Weapon::~Weapon() {
	type.clear();
}

Weapon Weapon::operator=(const Weapon &weapon) {
	type = weapon.type;
	return *this;
}


const std::string& Weapon::getType() {
	return this->type;
}

void Weapon::setType(std::string type) {
	this->type = type;
}
