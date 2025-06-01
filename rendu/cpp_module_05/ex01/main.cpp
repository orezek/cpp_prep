#include "Bureaucrat.hpp"
#include "Form.hpp"

int	main()
{
    {
        std::cout << "------------------" << std::endl;
        try
        {
            Bureaucrat plebAli = Bureaucrat("Ali", 147);
            Form form1 = Form("form1", 148, 8);
            std::cout << plebAli << std::endl;
            std::cout << form1 << std::endl;
            plebAli.signForm(form1);
            std::cout << form1 << std::endl;
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
            Bureaucrat plebAli = Bureaucrat("Ali", 149);
            Form form1 = Form("form1", 148, 8);
            std::cout << plebAli << std::endl;
            std::cout << form1 << std::endl;
            plebAli.signForm(form1);
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