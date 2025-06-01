#include "ASpell.hpp"

ASpell::ASpell(std::string name, std::string effects)
{
	this->name = name;
	this->effects = effects;
	}

ASpell::ASpell(const ASpell& refObj)
{
	this->name = refObj.name;
	this->effects = refObj.effects;
}

ASpell::~ASpell(){}

ASpell& ASpell::operator=(const ASpell& refObj)
{
	if (this != &refObj)
	{
		this->name = refObj.name;
		this->effects = refObj.effects;
	}
	return (*this);
}

const std::string& ASpell::getName() const
{
	return (this->name);
}

const std::string& ASpell::getEffects() const
{
	return (this->effects);
}

void ASpell::launch(ATarget& target) const
{
	target.getHitBySpell(*this);
}