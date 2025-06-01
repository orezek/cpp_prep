#include "SpellBook.hpp"


SpellBook::SpellBook() {};

SpellBook::~SpellBook() {
  this->_spellBook.clear();
};

void SpellBook::learnSpell(ASpell* spell) {
  if (spell) {
    std::map<std::string, ASpell*>::iterator it = this->_spellBook.find(spell->getName());
    if (it == this->_spellBook.end()) {
      this->_spellBook[spell->getName()] = spell->clone();
    }
  }
};

void SpellBook::forgetSpell(const std::string& spellName) {
  std::map<std::string, ASpell*>::iterator it = this->_spellBook.find(spellName);
  if (it != this->_spellBook.end()) {
    delete it->second;
    this->_spellBook.erase(spellName);
  }
};

ASpell* SpellBook::createSpell(const std::string& spellName) {
  std::map<std::string, ASpell*>::iterator it = this->_spellBook.find(spellName);
  if (it != this->_spellBook.end()) {
    return it->second->clone();
  }
  return nullptr;
};