#include "Bureaucrat.hpp"

// Purpose is to test exceptions!

int	main(void)
{

  {
    
    Bureaucrat a0s0 = Bureaucrat("A0s0", 150);
    Bureaucrat a1s1 = Bureaucrat("A1s1", 1);
    Bureaucrat a2s2 = Bureaucrat(); // default and maxGrade (1)

    std::cout << "------------------" << std::endl;
    std::cout << a0s0 << std::endl;
    std::cout << a1s1 << std::endl;
    std::cout << a2s2 << std::endl;
    std::cout << "------------------" << std::endl;

    // Decrement is + operation on the value
    // Increment is - operation on the value

    // Case 1: decrementing a2s2 - should pass - grade (1) + 1 = 2
    try
    {
      std::cout << "Case 1: decrementing a2s2" << std::endl;
      std::cout << "Trying to decrement '" << a2s2.getName() << "'" << std::endl;
      a2s2.decrementGrade();
    }
    catch (std::exception& e)
    {
      std::cerr << "Error: " << e.what() << std::endl;
    }

    // Case 2: decrementing a1s1 - should pass grade (1) + 1 = 2;
    try
    {
      std::cout << "Case 2: decrementing a1s1" << std::endl;
      std::cout << "Trying to decrement '" << a1s1.getName() << "'" << std::endl;
      a1s1.decrementGrade();
    }
    catch (std::exception& e)
    {
      std::cerr << "Error: " << e.what() << std::endl;
    }

    // Case: 3: incrementing a0s0 - should pass grade (150) - 1 = 149; 
    try
    {
      std::cout << "Case: 3: incrementing a0s0" << std::endl;
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
    // Case: 4: should fail - invalid grade range - too high!
    try
    {
      std::cout << "Case 4: invalid grade range - high grade" << std::endl;
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
    // Case: 5 should fail - invalid grade range -- too low!
    try
    {
      std::cout << "Case 5: invalid grade range - low grade" << std::endl;
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