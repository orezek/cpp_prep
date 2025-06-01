#include "SpellBook.hpp"

SpellBook::SpellBook() {}

SpellBook::~SpellBook() {}

void SpellBook::learnSpell(ASpell *aSpell)
{
	if (aSpell == NULL)
	{
		return;
	}
	for (std::vector<ASpell *>::iterator it = spells.begin(); it != spells.end(); ++it)
	{
		if (aSpell->getName() == (*it)->getName())
			return;
	}
	spells.push_back(aSpell->clone());
}

void SpellBook::forgetSpell(std::string const &spellName)
{
	for (std::vector<ASpell *>::iterator it = spells.begin(); it != spells.end(); ++it)
	{
		if (spellName == (*it)->getName())
		{
			spells.erase(it);
			return;
		}
	}
}

ASpell* SpellBook::createSpell(std::string const &spellName)
{
	for (std::vector<ASpell *>::iterator it = spells.begin(); it != spells.end(); ++it)
	{
		if (spellName == (*it)->getName())
		{
			return((*it)->clone());
		}
	}
	return (NULL);
}
