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
	spellBook.learnSpell(aSpell);
}
void Warlock::forgetSpell(std::string spellName)
{
	spellBook.forgetSpell(spellName);
}

void Warlock::launchSpell(std::string spellName, ATarget &aTarget)
{
	ASpell* tempSpell = spellBook.createSpell(spellName);
	if (tempSpell != NULL)
	{
		tempSpell->launch(aTarget);
	}
}