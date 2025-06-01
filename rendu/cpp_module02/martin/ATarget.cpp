#include "ATarget.hpp"

ATarget::ATarget(std::string type)
{
	this->type = type;
}

ATarget::ATarget(const ATarget& refObj)
{
	this->type = refObj.type;
}

ATarget::~ATarget() {}

ATarget& ATarget::operator=(const ATarget& refObj)
{
	if (this != &refObj)
	{
		this->type = refObj.type;
	}
	return (*this);
}

const std::string& ATarget::getType() const
{
	return (this->type);
}

void ATarget::getHitBySpell(const ASpell& spell) const
{
	std::cout << this->type << " has been " << spell.getEffects() << "!" << std::endl;

}