#pragma once
#include <string>
#include <iostream>
#include <map>

#include "ASpell.hpp"
#include "ATarget.hpp"

class ASpell;
class ATarget;

class SpellBook {
  public:
    SpellBook();
    ~SpellBook();
    void learnSpell(ASpell* spell);
    void forgetSpell(const std::string& spellName);
    ASpell* createSpell(const std::string& spellName);
  private:
    std::map<std::string, ASpell*> _spellBook;
    SpellBook(const SpellBook& other);
    SpellBook& operator=(const SpellBook& other);
};