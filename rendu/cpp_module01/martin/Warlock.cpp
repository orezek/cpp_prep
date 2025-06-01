#include "Warlock.hpp"

Warlock::Warlock(std::string name, std::string title)
{
	this->name = name;
	this->title = title;
	std::cout << this->name << ": This looks like another boring day." << std::endl;
}

Warlock::~Warlock()
{
	std::cout << this->name << ": My job here is done!" << std::endl;
}

const std::string &Warlock::getName() const
{
	return (this->name);
}

const std::string &Warlock::getTitle() const
{
	return (this->title);
}

void Warlock::setTitle(const std::string &newTitle)
{
	this->title = newTitle;
}

void Warlock::introduce() const
{
	std::cout << this->name << ": I am " << this->name << ", " << this->title << "!" << std::endl;
}

void Warlock::learnSpell(ASpell *aSpell)
{
	if (aSpell)
	{
		for (std::vector<ASpell*>::iterator it = spells.begin(); it != spells.end(); ++it)
		{
			if ((*it)->getName() == aSpell->getName())
			{
				return;
			}
		}
		this->spells.push_back(aSpell);
	}
}
void Warlock::forgetSpell(std::string spellName)
{
	for (std::vector<ASpell*>::iterator it = spells.begin(); it != spells.end(); ++it)
	{
		if ((*it)->getName() == spellName)
		{
			spells.erase(it);
			return;
		}
	}
}

void Warlock::launchSpell(std::string spellName, ATarget &aTarget)
{
	for (std::vector<ASpell*>::iterator it = spells.begin(); it != spells.end(); ++it)
	{
		if ((*it)->getName() == spellName)
		{
			(*it)->launch(aTarget);
			return;
		}
	}
}