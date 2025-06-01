#include "Form.hpp"


Form::Form() : _name(""), _isSigned(false), _gradeRequiredToSign(MIN_GRADE), _gradeRequiredToExecute(MIN_GRADE)
{}

Form::Form(std::string name, int gradeToSign, int gradeToExecute) : _name(name), _isSigned(false),
        _gradeRequiredToSign((gradeToSign > MIN_GRADE) ? throw Form::GradeTooLowException() : (gradeToSign < MAX_GRADE) ? throw Form::GradeTooHighException() : gradeToSign),
        _gradeRequiredToExecute((gradeToExecute > MIN_GRADE) ? throw Form::GradeTooLowException() : (gradeToExecute < MAX_GRADE) ? throw Form::GradeTooHighException() : gradeToExecute)
{}

Form::Form(const Form& refObj) : _name(refObj._name), _isSigned(refObj._isSigned), _gradeRequiredToSign(refObj._gradeRequiredToSign), _gradeRequiredToExecute(refObj._gradeRequiredToExecute)
{}

// Does not make so much sense because of const variables - both objects already exists with const _name which is immutable!
// I could delete the assignment operator like adding = delete;
Form& Form::operator=(const Form& refObj)
{
    _isSigned = refObj._isSigned;
    return(*this);
}

Form::~Form() {}

std::string	Form::getName() const {
  return this->_name;
}

bool Form::getIsSigned() const {
  return this->_isSigned;
}

int	Form::getGradeRequiredToSign() const {
  return this->_gradeRequiredToSign;
}

int	Form::getGradeRequiredToExecute() const {
  return this->_gradeRequiredToExecute;
}

void	Form::beSigned(Bureaucrat& bureaucrat)
{
    if (this->getGradeRequiredToSign() < bureaucrat.getGrade())
        throw Form::GradeTooLowException();
    this->_isSigned = true;
}

const char *Form::GradeTooHighException::what(void) const throw()
{
    return ("Grade is too high!");
}

const char *Form::GradeTooLowException::what(void) const throw()
{
    return ("Grade is too low!");
}


std::ostream&	operator<<(std::ostream &outputStream, const Form& form)
{
    outputStream << "Form: '" << form.getName();
    outputStream << "', grade required to sign: " << form.getGradeRequiredToSign();
    outputStream << ", grade required to execute: " << form.getGradeRequiredToExecute();
    outputStream << ", signed: " << form.getIsSigned() << ".";
    return(outputStream);
}