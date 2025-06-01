#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat() : name(""), grade(MINIMUM_GRADE)
{}

Bureaucrat::Bureaucrat(const std::string name, int grade) : name(name)
{
	if (grade < MAXIMUM_GRADE)
		throw Bureaucrat::GradeTooHighException();
	if (grade > MINIMUM_GRADE)
		throw Bureaucrat::GradeTooLowException();
	this->grade = grade;
}

Bureaucrat::Bureaucrat(const Bureaucrat& refObj) : grade(refObj.grade)
{}

Bureaucrat& Bureaucrat::operator=(const Bureaucrat& refObj)
{
	grade = refObj.grade;
	return (*this);
}

Bureaucrat::~Bureaucrat()
{}

void	Bureaucrat::incrementGrade()
{
	if (grade - 1 < MAXIMUM_GRADE)
		throw Bureaucrat::GradeTooHighException();
	grade--;
}

void	Bureaucrat::decrementGrade()
{
	if (grade + 1 > MINIMUM_GRADE)
		throw Bureaucrat::GradeTooLowException();
	grade++;
}

int Bureaucrat::getGrade() const
{
	return (grade);
}

const std::string Bureaucrat::getName() const
{
	return (name);
}


void	Bureaucrat::signForm(AForm& form)
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

void Bureaucrat::executeForm(AForm const & form) const
{
	try
	{
		form.execute(*this);
		std::cout << this->name << " executed " << form.getName() << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << this->getName() << " couldn't execute " << form.getName() << " because: " << e.what() << std::endl;
	}
}

const char *Bureaucrat::GradeTooHighException::what(void) const throw()
{
	return ("Grade too high! 1 is maximum-ultra-high king of everything grade!");
}

const char *Bureaucrat::GradeTooLowException::what(void) const throw()
{
	return ("Grade too low! 150 is minimum grade for the lowest pleb bureaucrat!");
}

std::ostream&	operator<<(std::ostream &outputStream, const Bureaucrat& bureaucrat)
{
	outputStream << "'" << bureaucrat.getName() << "', bureaucrat grade " << bureaucrat.getGrade();
	return (outputStream);
}