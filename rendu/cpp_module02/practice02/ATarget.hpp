#pragma once
#include <string>
#include <iostream>
#include "ASpell.hpp"

class ASpell;


class ATarget {
  public:
    ATarget(const std::string type);
    virtual ~ATarget();
    virtual ATarget* clone() const = 0;
    const std::string& getType(void) const;
    void getHitBySpell(const ASpell& spell) const;
  protected:
    std::string _type;
};