#pragma once
#include <string>
#include <iostream>

class Warlock {
  public:
    Warlock(const std::string& name, const std::string& title);
    ~Warlock();
    const std::string& getName() const;
    const std::string& getTitle() const;
    void setTitle(const std::string newTitle);
    void introduce(void) const;
  private:
    Warlock();
    Warlock(const Warlock& other);
    Warlock& operator=(const Warlock& other);
    std::string _name;
    std::string _title;

};