#pragma once
#include <string>
#include <iostream>
#include <map>
#include "ASpell.hpp"
#include "ATarget.hpp"

class ASpell;
class ATarget;


class Warlock {
  public:
    Warlock(const std::string& name, const std::string& title);
    ~Warlock();
    const std::string& getName() const;
    const std::string& getTitle() const;
    void setTitle(const std::string newTitle);
    void introduce(void) const;
    void learnSpell(ASpell* spell);
    void forgetSpell(std::string spellName);
    void launchSpell(std::string spellName, ATarget& target);
  private:
    Warlock();
    Warlock(const Warlock& other);
    Warlock& operator=(const Warlock& other);
    std::string _name;
    std::string _title;
    std::map<std::string, ASpell*> _spellBook;
};