#pragma once
#include "ATarget.hpp"
#include <string>
#include <iostream>
#include <map>

class ATarget;

class TargetGenerator {
  public:
    TargetGenerator();
    ~TargetGenerator();
    void learnTargetType(ATarget* target);
    void forgetTargetType(const std::string& target);
    ATarget* createTarget(const std::string& target);
  private:
  TargetGenerator(const TargetGenerator& other);
  TargetGenerator& operator=(const TargetGenerator& other);
  std::map<std::string, ATarget*> _targets;
};