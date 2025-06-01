#pragma once

#include <string>
#include <iostream>
#include <map>

#include "ATarget.hpp"

class ATarget;

class ASpell
{
public:
	ASpell(std::string name, std::string effects);
	ASpell(const ASpell &);
	virtual ~ASpell();
	const std::string &getName() const;
	const std::string &getEffects() const;
	virtual ASpell *clone() = 0;
	void launch(ATarget&) const;

protected:
	ASpell &operator=(const ASpell &);
	std::string name;
	std::string effects;
};