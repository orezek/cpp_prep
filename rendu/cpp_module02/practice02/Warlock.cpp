#include "Warlock.hpp"



Warlock::Warlock(const std::string& name, const std::string& title) : _name(name), _title(title) {
  std::cout << this->_name << ": This looks like another boring day." << std::endl;
};
Warlock::~Warlock() {
  std::cout << this->_name << ": My job here is done!" << std::endl;
};

const std::string& Warlock::getTitle() const {
  return this->_title;
};

const std::string& Warlock::getName() const {
  return this->_name;
};

void Warlock::setTitle(const std::string newTitle) {
  this->_title = newTitle;
};

void Warlock::introduce(void) const {
  std::cout << this->_name << ": I am " << this->_name << ", " << this->_title << "!" << std::endl;;
};

void Warlock::learnSpell(ASpell* spell) {
  this->spellBook.learnSpell(spell);
};

void Warlock::forgetSpell(std::string spellName) {
  this->spellBook.forgetSpell(spellName);
};

void Warlock::launchSpell(std::string spellName, ATarget& target) {
  ASpell* spell = this->spellBook.createSpell(spellName);
  if (spell) {
    spell->launch(target);
    delete spell;
  }
};