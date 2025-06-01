#pragma once

#include <string>
#include <iostream>

#include "ASpell.hpp"

class Fireball : public ASpell
{
public:
	Fireball();
	Fireball *clone();
	~Fireball();

private:
};