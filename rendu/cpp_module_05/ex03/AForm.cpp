#include "AForm.hpp"


AForm::AForm() : name(""), isSigned(false), gradeRequiredToSign(MINIMUM_GRADE), gradeRequiredToExecute(MINIMUM_GRADE)
{}

AForm::AForm(const std::string name, int gradeToSign, int gradeToExecute) : name(name), isSigned(false),
		gradeRequiredToSign((gradeToSign > MINIMUM_GRADE) ? throw AForm::GradeTooLowException() : (gradeToSign < MAXIMUM_GRADE) ? throw AForm::GradeTooHighException() : gradeToSign),
		gradeRequiredToExecute((gradeToExecute > MINIMUM_GRADE) ? throw AForm::GradeTooLowException() : (gradeToExecute < MAXIMUM_GRADE) ? throw AForm::GradeTooHighException() : gradeToExecute)
{}

AForm::AForm(const AForm& refObj) : name(refObj.name), isSigned(refObj.isSigned), gradeRequiredToSign(refObj.gradeRequiredToSign), gradeRequiredToExecute(refObj.gradeRequiredToExecute)
{}

// Does not make so much sense because of const variables
AForm& AForm::operator=(const AForm& refObj)
{
	isSigned = refObj.isSigned;
	return(*this);
}

AForm::~AForm() {}

std::string	AForm::getName() const {return (name);}
bool	AForm::getIsSigned() const {return (isSigned);}
int	AForm::getGradeRequiredToSign() const {return (gradeRequiredToSign);}
int	AForm::getGradeRequiredToExecute() const {return (gradeRequiredToExecute);}

void	AForm::beSigned(Bureaucrat& bureaucrat)
{
	if (this->getGradeRequiredToSign() < bureaucrat.getGrade())
		throw AForm::GradeTooLowException();
	this->isSigned = true;
}

const char *AForm::GradeTooHighException::what(void) const throw()
{
	return ("Grade is too high!");
}

const char *AForm::GradeTooLowException::what(void) const throw()
{
	return ("Grade is too low!");
}

const char *AForm::NotSignedException::what(void) const throw()
{
	return ("Form is not signed!");
}

std::ostream&	operator<<(std::ostream &outputStream, const AForm& form)
{
	outputStream << "Form: '" << form.getName();
	outputStream << "', grade required to sign: " << form.getGradeRequiredToSign();
	outputStream << ", grade required to execute: " << form.getGradeRequiredToExecute();
	outputStream << ", signed: " << form.getIsSigned() << ".";
	return(outputStream);
}