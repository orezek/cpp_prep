#include "Bureaucrat.hpp"
#include "Form.hpp"

// Purpose using exceptions in methods (signForm()).

//form - (std::string name, int gradeToSign, int gradeToExecute) : _name(name), _isSigned(false)
//bureaucrat - const std::string& name, int grade


// bureaucrat cannot execute form yet!

int	main()
{
    {
        // Case 1: testing if bureaucrat can sign the form
        // Should pass! grade higher or equal (in opposite sense)
        std::cout << "Case 1:" << std::endl;
        try
        {

            Bureaucrat a1s1 = Bureaucrat("a1s1", 147);
            Form form1 = Form("form1", 148, 8);
            std::cout << a1s1 << std::endl;
            std::cout << form1 << std::endl;
            a1s1.signForm(form1);
            std::cout << form1 << std::endl;
        }
        catch (std::exception& e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
        std::cout << "------------------" << std::endl;
    }


    {
        // Case 2: testing if the bureaucrat can sign the form
        // Should fail! grade higher or equal (in opposite sense)
        std::cout << "Case 2:" << std::endl;
        try
        {
            Bureaucrat a1s1 = Bureaucrat("a1s1", 149);
            Form form1 = Form("form1", 148, 8);
            std::cout << a1s1 << std::endl;
            std::cout << form1 << std::endl;
            a1s1.signForm(form1);
            std::cout << form1 << std::endl;
        }
        catch (std::exception& e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
        std::cout << "------------------" << std::endl;
    }

    return (0);
}