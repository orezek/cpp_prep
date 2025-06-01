#include "Bureaucrat.hpp"

int	main(void)
{
  {
    Bureaucrat a0s0 = Bureaucrat("A0s0", 150);
    Bureaucrat a1s1 = Bureaucrat("A1s1", 1);
    Bureaucrat a2s2 = Bureaucrat();

    std::cout << "------------------" << std::endl;
    std::cout << a0s0 << std::endl;
    std::cout << a1s1 << std::endl;
    std::cout << a2s2 << std::endl;
    std::cout << "------------------" << std::endl;

    try
    {
      std::cout << "Trying to decrement '" << a2s2.getName() << "'" << std::endl;
      a2s2.decrementGrade();
    }
    catch (std::exception& e)
    {
      std::cerr << "Error: " << e.what() << std::endl;
    }


    try
    {
      std::cout << "Trying to decrement '" << a1s1.getName() << "'" << std::endl;
      a1s1.decrementGrade();
    }
    catch (std::exception& e)
    {
      std::cerr << "Error: " << e.what() << std::endl;
    }


    try
    {
      std::cout << "Trying to increment '" << a0s0.getName() << "'" << std::endl;
      a0s0.incrementGrade();
    }
    catch (std::exception& e)
    {
      std::cerr << "Error: " << e.what() << std::endl;
    }
  }


  {
    std::cout << "------------------" << std::endl;
    try
    {
      std::cout << "Trying to create bureaucrat with grade 0" << std::endl;
      Bureaucrat highGrade = Bureaucrat("Boss", 0);
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
      std::cout << "Trying to create bureaucrat with grade 151" << std::endl;
      Bureaucrat highGrade = Bureaucrat("Boss", 151);
    }
    catch (std::exception& e)
    {
      std::cerr << "Error: " << e.what() << std::endl;
    }
    std::cout << "------------------" << std::endl;
  }

  return (0);
}