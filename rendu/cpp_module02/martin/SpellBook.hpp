#pragma once

#include <string>
#include <iostream>
#include <vector>

#include "ASpell.hpp"

class SpellBook
{
	public:
		SpellBook();
		~SpellBook();
		void learnSpell(ASpell*); //, that COPIES a spell in the book
		void forgetSpell(std::string const &); //, that deletes a spell from the book, except if it isn't there
		ASpell* createSpell(std::string const &); //, that receives a string corresponding to the name of a spell, creates it, and returns it.


	private:
		std::vector<ASpell*> spells;
		SpellBook(const SpellBook&);
		SpellBook& operator=(const SpellBook&);
};