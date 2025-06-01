#include "TargetGenerator.hpp"

TargetGenerator::TargetGenerator() {}

TargetGenerator::~TargetGenerator() {}

void TargetGenerator::learnTargetType(ATarget *aTarget)
{
	if (aTarget == NULL)
	{
		return;
	}
	for (std::vector<ATarget *>::iterator it = targets.begin(); it != targets.end(); ++it)
	{
		if (aTarget->getType() == (*it)->getType())
			return;
	}
	targets.push_back(aTarget->clone());
}

void TargetGenerator::forgetTargetType(std::string const &spellName)
{
	for (std::vector<ATarget *>::iterator it = targets.begin(); it != targets.end(); ++it)
	{
		if (spellName == (*it)->getType())
		{
			targets.erase(it);
			return;
		}
	}
}

ATarget* TargetGenerator::createTarget(std::string const &spellName)
{
	for (std::vector<ATarget *>::iterator it = targets.begin(); it != targets.end(); ++it)
	{
		if (spellName == (*it)->getType())
		{
			return((*it)->clone());
		}
	}
	return (NULL);
}
