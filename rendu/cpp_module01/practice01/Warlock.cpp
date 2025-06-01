#include "Warlock.hpp"



Warlock::Warlock(const std::string& name, const std::string& title) : _name(name), _title(title) {
  std::cout << this->_name << ": This looks like another boring day." << std::endl;
};
Warlock::~Warlock() {
  std::cout << this->_name << ": My job here is done!" << std::endl;
  this->_spellBook.clear();
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
  if (spell) {
    std::map<std::string, ASpell*>::iterator it = this->_spellBook.find(spell->getName());
    if (it == this->_spellBook.end()) {
      this->_spellBook[spell->getName()] = spell->clone();
    }
  }
};

void Warlock::forgetSpell(std::string spellName) {
  std::map<std::string, ASpell*>::iterator it = this->_spellBook.find(spellName);
  if (it != this->_spellBook.end()) {
    delete it->second;
    this->_spellBook.erase(spellName);
  }
};

void Warlock::launchSpell(std::string spellName, ATarget& target) {
  std::map<std::string, ASpell*>::iterator it = this->_spellBook.find(spellName);
  if (it != this->_spellBook.end()) {
    it->second->launch(target);
  }
};