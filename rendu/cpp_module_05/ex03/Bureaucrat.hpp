#pragma once
#include <iostream>
#include <string>

#include "AForm.hpp"

#define MINIMUM_GRADE 150
#define MAXIMUM_GRADE 1

class AForm;

class Bureaucrat
{
private:
    const std::string	name;
    int					grade;

public:
    Bureaucrat();
    Bureaucrat(std::string name, int grade);
    Bureaucrat(const Bureaucrat&);
    Bureaucrat& operator=(const Bureaucrat&);
    ~Bureaucrat();

    const std::string	getName() const;
    int					getGrade() const;
    void				decrementGrade();
    void				incrementGrade();

    void	signForm(AForm&);

    void	executeForm(AForm const & form);

    //Exceptions
    class GradeTooLowException : public std::exception
    {
    public:
        virtual const char *what() const throw();
    };

    class GradeTooHighException : public std::exception
    {
    public:
        virtual const char *what() const throw();
    };
};

std::ostream&	operator<<(std::ostream &outputStream, const Bureaucrat& bureaucrat);

