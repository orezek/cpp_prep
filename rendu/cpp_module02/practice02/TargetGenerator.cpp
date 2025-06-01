#include "TargetGenerator.hpp"

TargetGenerator::TargetGenerator() {};

TargetGenerator::~TargetGenerator() {
  this->_targets.clear();
};

void TargetGenerator::learnTargetType(ATarget* target) {
  if (target) {
    std::map<std::string, ATarget*>::iterator it = this->_targets.find(target->getType());
    if (it == this->_targets.end()) {
      this->_targets[target->getType()] = target->clone();
    }
  }
};

void TargetGenerator::forgetTargetType(const std::string& target) {
  std::map<std::string, ATarget*>::iterator it = this->_targets.find(target);
  if (it != this->_targets.end()) {
    delete it->second;
    this->_targets.erase(target);
  }
};

ATarget* TargetGenerator::createTarget(const std::string& target) {
  std::map<std::string, ATarget*>::iterator it = this->_targets.find(target);
  if (it != this->_targets.end()) {
    return it->second->clone();
  }
  return nullptr;
};