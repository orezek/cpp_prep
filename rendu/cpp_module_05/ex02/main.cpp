
#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

// Purpose: Learn to use abstract class use and pure virtual methods implementation.
// Each execute function in the concrete Form class does something little different.

// Abstract vs concrete


/*
Base class is not abstract (no "abstract" keyword in C++, abstractness is implied by pure virtuals).
Why virtual specifier is needed? Is it actually needed? -> Only for dynamic dispatch!
 */

int	main()
{
	{
		// Case 1: test form signature and execution of ShrubberyCreationForm - should pass and creates ASCI tree file
		std::cout << "Case 1: ShrubberyCreationForm" << std::endl;
		try
		{
            // Direct initializtion
			Bureaucrat a1s1("A1s1", 1); //= Bureaucrat("A1s1", 1);
            // Copy initialization
			// "ShrubberyCreationForm", 145, 137
			ShrubberyCreationForm form1 = ShrubberyCreationForm("target");

			std::cout << a1s1 << std::endl;
			std::cout << form1 << std::endl;
			// checks grades
			a1s1.signForm(form1);
			std::cout << form1 << std::endl;
			// checks if form is signed and grade for execution is correct
			a1s1.executeForm(form1);
		}
		catch (std::exception& e)
		{
			std::cerr << "Error: " << e.what() << std::endl;
		}

		std::cout << "------------------" << std::endl;
	}
	//----------------------------------------------------

	{
		// Case 2: "RobotomyRequestForm", 72, 45 - should pass by grades by my fail due to randomness
		std::cout << "Case 2: RobotomyRequestForm" << std::endl;
		try
		{
			Bureaucrat a1s1 = Bureaucrat("A1s1", 26);
			RobotomyRequestForm form1 = RobotomyRequestForm("target123");

			std::cout << a1s1 << std::endl;
			std::cout << form1 << std::endl;

			a1s1.signForm(form1);
			std::cout << form1 << std::endl;
			// testing 1/2 randomness
			for (int i = 0; i < 10; i++)
				a1s1.executeForm(form1);
		}
		catch (std::exception& e)
		{
			std::cerr << "Error: " << e.what() << std::endl;
		}
		std::cout << "------------------" << std::endl;
	}
	// ------------------------------------------------------

	{
		// Case 3: "PresidentialPardonForm", 25, 5 - should fail due to grades
		std::cout << "Case 3: PresidentialPardonForm" << std::endl;
		try
		{
			Bureaucrat a1s1 = Bureaucrat("A1s1", 6);
			PresidentialPardonForm form1 = PresidentialPardonForm("targetPresident");

			// Testing dynamic dispatch
//			AForm* form2 = new PresidentialPardonForm("targetPresident");
//          std::cout << form2->getName() << std::endl;


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
	//----------------------------------------------------------

		{
		// Case 4: "PresidentialPardonForm", 25, 5 - should pass and print " has been pardoned by Zaphod Beeblebrox."
		std::cout << "Case 4: PresidentialPardonForm" << std::endl;
		try
		{
			Bureaucrat a1s1 = Bureaucrat("A1s1", 4);
			PresidentialPardonForm form1 = PresidentialPardonForm("targetPresident");
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