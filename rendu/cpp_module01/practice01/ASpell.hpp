#pragma once
#include <string>
#include <iostream>
#include "ATarget.hpp"

class ATarget;

class ASpell {
  public:
    ASpell(const std::string& name, const std::string& effects);
    virtual ~ASpell();
    virtual ASpell* clone() const = 0;
    std::string getName() const;
    std::string getEffects() const;
    void launch(const ATarget& target);
  protected:
    std::string _name;
    std::string _effects;
};