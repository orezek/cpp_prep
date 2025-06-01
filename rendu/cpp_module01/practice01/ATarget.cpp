#include "ATarget.hpp"


ATarget::ATarget(const std::string type) : _type(type) {};

ATarget::~ATarget() {};

const std::string& ATarget::getType(void) const {
  return this->_type;
};

void ATarget::getHitBySpell(const ASpell& spell) const {
  std::cout << this->_type << " has been " << spell.getEffects() << "!" << std::endl;
};