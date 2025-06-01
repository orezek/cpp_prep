#include "Bureaucrat.hpp"

/*
Purpose learn to use custom exeptions.
 */


// Default constructor
Bureaucrat::Bureaucrat() : _name("default"), _grade(MAX_GRADE) {
  std::cout << "Bureaucrat default constructor was invoked. Name: " << this->getName() << "Grade: " << this->getGrade() << "." << std::endl;
};

// Parametrized constructor
Bureaucrat::Bureaucrat(const std::string& name, int grade) : _name(name) {
  if (grade < MAX_GRADE) {
    throw Bureaucrat::GradeTooHighException();
  }
  if (grade > MIN_GRADE) {
    throw Bureaucrat::GradeTooLowException();
  }
  this->_grade = grade;
};

// Copy constructor
// Need to use initialization list to assing _name which is declared as const in the class def.
Bureaucrat::Bureaucrat(const Bureaucrat& other) : _name(other.getName()) {
  std::cout << "Bureaucrat copy constructor called." << std::endl;
  // using assignment operator to re-use code.
  *this = other;
};

// Operator overloading
Bureaucrat& Bureaucrat::operator=(const Bureaucrat& other) {
  std::cout << "Bureaucrat assignment operator called." << std::endl;
  if (this != &other) {
    this->_grade = other.getGrade();
    return *this;
  }
  return *this;
};

// Destructor
Bureaucrat::~Bureaucrat() {
  std::cout << "Bureaucrat destructor called." << std::endl;
};


// Public methods
const std::string& Bureaucrat::getName(void) const {
  return this->_name;
};

int Bureaucrat::getGrade(void) const {
  return this->_grade;
};

void Bureaucrat::incrementGrade(void) {
  if (_grade - 1 < MAX_GRADE) {
    throw Bureaucrat::GradeTooHighException();
  }
  this->_grade--;
};

void Bureaucrat::decrementGrade(void) {
  if (_grade + 1 > MIN_GRADE) {
    throw Bureaucrat::GradeTooLowException();
  }
  this->_grade++;
};

void	Bureaucrat::signForm(Form& form)
{
  try
  {
    form.beSigned(*this);
    std::cout << this->getName() << " signed " << form.getName() << std::endl;
  }
  catch (std::exception& e)
  {
    std::cout << this->getName() << " couldn't sign " << form.getName() << " because: " << e.what() << std::endl;
  }
}



// Execptions
const char *Bureaucrat::GradeTooHighException::what(void) const throw() {
  return ("Grade too high!!");
};

const char *Bureaucrat::GradeTooLowException::what(void) const throw() {
  return ("Grade too low!!");
};

// Insertion operator overloading
std::ostream&	operator<<(std::ostream &outputStream, const Bureaucrat& bureaucrat)
{
  outputStream << bureaucrat.getName() << "', bureaucrat grade " << bureaucrat.getGrade();
  return (outputStream);
};