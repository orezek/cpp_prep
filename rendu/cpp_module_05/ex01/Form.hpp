#pragma once
#include "Bureaucrat.hpp"

/*
The purpose is to learn to use custom exeptions.
*/



// Forward declaration to satisfy the compiler greed.
class Bureaucrat;

class Form
{
private:
    const std::string _name;
    bool _isSigned;
    const int _gradeRequiredToSign;
    const int _gradeRequiredToExecute;

public:
    Form();
    Form(std::string _name, int gradeRequiredToSign, int gradeRequiredToExecute);
    Form(const Form&);
    Form& operator=(const Form&);
    ~Form();

    // Members
    std::string	getName() const;
    bool		getIsSigned() const;
    int			getGradeRequiredToSign() const;
    int			getGradeRequiredToExecute() const;
    void		beSigned(Bureaucrat&);

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

std::ostream&	operator<<(std::ostream &outputStream, const Form& form);
