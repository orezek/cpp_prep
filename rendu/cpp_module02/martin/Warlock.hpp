#pragma once

#include <iomanip>
#include <iostream>
#include <string>

#include "ASpell.hpp"
#include "ATarget.hpp"

#include <vector>
#include <algorithm>
#include "SpellBook.hpp"

class Warlock
{
public:
	const std::string &getName() const;
	const std::string &getTitle() const;
	void setTitle(const std::string &newTitle);
	Warlock(std::string name, std::string title);
	~Warlock();
	void introduce() const;

	void learnSpell(ASpell *);
	void forgetSpell(std::string spellName);
	void launchSpell(std::string spellName, ATarget& aTarget);

private:
	SpellBook spellBook;
	Warlock();
	Warlock(const Warlock &);
	Warlock &operator=(const Warlock &);
	std::string name;
	std::string title;
	std::vector<ASpell*> spells;
};