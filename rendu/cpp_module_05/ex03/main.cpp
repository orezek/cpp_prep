#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"


// Purpose is to implement class that has function that returns a specific type of other class (form) i.e Factory function

int	main()
{
	{
		std::cout << "Case 1: create forms" << std::endl;

		Intern intern;
		AForm* form;

		try
		{
			form = intern.makeForm("PresidentialPardonForm", "Target1");
			delete form;

			form = intern.makeForm("RobotomyRequestForm", "Target2");
			delete form;

			form = intern.makeForm("ShrubberyCreationForm", "Target3");
			delete form;
			
			// Should fail
			form = intern.makeForm("UnknownForm", "Target4");
			delete form;
		}
		catch (std::exception& e)
		{
			std::cerr << "Error: " << e.what() << std::endl;
		}
		std::cout << "------------------" << std::endl;
	}


	{
		std::cout << "Case 2: create forms and sign and execute" << std::endl;
		try
		{
			Intern intern;
			AForm* form;

			Bureaucrat plebAli = Bureaucrat("Ali", 1);
			form = intern.makeForm("ShrubberyCreationForm", "Target3");

			std::cout << plebAli << std::endl;
			std::cout << *form << std::endl;

			plebAli.signForm(*form);
			std::cout << *form << std::endl;
			plebAli.executeForm(*form);

			delete form;
		}
		catch (std::exception& e)
		{
			std::cerr << "Error: " << e.what() << std::endl;
		}
		std::cout << "------------------" << std::endl;
	}

	return (0);
}