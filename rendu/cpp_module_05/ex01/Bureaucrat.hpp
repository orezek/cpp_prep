#pragma once
#include <string>
#include <iostream>
#include "Form.hpp"

#define MIN_GRADE 150
#define MAX_GRADE 1

class Form;

class Bureaucrat {

  public:
    Bureaucrat();
    Bureaucrat(const std::string& _name, int _grade);
    Bureaucrat(const Bureaucrat& other);
    Bureaucrat& operator=(const Bureaucrat& other);
    ~Bureaucrat();

    const std::string& getName(void) const;
    int getGrade(void) const;
    void incrementGrade(void);
    void decrementGrade(void);
    void signForm(Form& form);

    class GradeTooLowException : public std::exception {
      public:
        virtual const char* what() const throw();
    };

    class GradeTooHighException : public std::exception {
      public:
        virtual const char* what() const throw();
    };

  private:
    const std::string _name;
    int _grade;
};

std::ostream& operator<<(std::ostream& outStream, const Bureaucrat& bureaucrat);