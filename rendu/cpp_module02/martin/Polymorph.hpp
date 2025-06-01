#pragma once

#include <string>
#include <iostream>

#include "ASpell.hpp"

class Polymorph : public ASpell
{
public:
	Polymorph();
	Polymorph *clone();
	~Polymorph();

private:
};