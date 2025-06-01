#include "Intern.hpp"

Intern::Intern() {}
Intern::Intern(const Intern&) {}
Intern& Intern::operator=(const Intern&) { return (*this); }
Intern::~Intern() {};


AForm*	Intern::createPresidentialPardonForm(const std::string target)
{
	return( new PresidentialPardonForm(target) );
}

AForm*	Intern::createRobotomyRequestForm(const std::string target)
{
	return( new RobotomyRequestForm(target) );
}

AForm*	Intern::createShrubberyCreationForm(const std::string target)
{
	return( new ShrubberyCreationForm(target) );
}

// Factory function to create specific types of forms

/*
pointer to a function:
AForm* (*formFuncs)(const std::string);
array of pointers to the static factory methods in the class

*/

AForm*	Intern::makeForm(const std::string formName, const std::string formTarget)
{
	const std::string	formNamePrototypes[3] = {"PresidentialPardonForm", "RobotomyRequestForm", "ShrubberyCreationForm"};

	typedef AForm* (*formFuncs)(const std::string);
	formFuncs funcs[3] = {
		&Intern::createPresidentialPardonForm,
		&Intern::createRobotomyRequestForm,
		&Intern::createShrubberyCreationForm
	};

	for (int i = 0; i < 3; i++)
	{
		if (formName == formNamePrototypes[i])
		{
			std::cout << "Intern creates " << formName << std::endl;
			return (funcs[i](formTarget));
		}
	}
	throw Intern::UnknownForm();
	return (NULL);
}

const char *Intern::UnknownForm::what(void) const throw()
{
	return ("The desired type of the form was not found!");
}