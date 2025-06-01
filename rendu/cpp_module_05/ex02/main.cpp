
#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"


/*
Base class is not abstract (no "abstract" keyword in C++, abstractness is implied by pure virtuals).
Why virtual specifier is needed? Is it?
 */

int	main()
{
	{
		std::cout << "------------------" << std::endl;
		try
		{
            // Direct initializtion
			Bureaucrat a1s1("A1s1", 1); //= Bureaucrat("A1s1", 1);
            // Copy initialization
			ShrubberyCreationForm form1 = ShrubberyCreationForm("target");

			std::cout << a1s1 << std::endl;
			std::cout << form1 << std::endl;

			a1s1.signForm(form1);
			std::cout << form1 << std::endl;
			a1s1.executeForm(form1);
		}
		catch (std::exception& e)
		{
			std::cerr << "Error: " << e.what() << std::endl;
		}

		std::cout << "------------------" << std::endl;
	}
	{
		std::cout << "------------------" << std::endl;
		try
		{
			Bureaucrat a1s1 = Bureaucrat("A1s1", 26);
			RobotomyRequestForm form1 = RobotomyRequestForm("target123");

			std::cout << a1s1 << std::endl;
			std::cout << form1 << std::endl;

			a1s1.signForm(form1);
			std::cout << form1 << std::endl;
			for (int i = 0; i < 10; i++)
				a1s1.executeForm(form1);
		}
		catch (std::exception& e)
		{
			std::cerr << "Error: " << e.what() << std::endl;
		}
		std::cout << "------------------" << std::endl;
	}
	{
		std::cout << "------------------" << std::endl;
		try
		{
			Bureaucrat a1s1 = Bureaucrat("A1s1", 6);
			PresidentialPardonForm form1 = PresidentialPardonForm("targetPresident");
//			AForm* form2 = new PresidentialPardonForm("targetPresident");
//            std::cout << form2->getName() << std::endl;


			std::cout << a1s1 << std::endl;
			std::cout << form1 << std::endl;

			a1s1.signForm(form1);
			std::cout << form1 << std::endl;
			a1s1.executeForm(form1);
		}
		catch (std::exception& e)
		{
			std::cerr << "Error: " << e.what() << std::endl;
		}
		std::cout << "------------------" << std::endl;
	}
	return (0);
}