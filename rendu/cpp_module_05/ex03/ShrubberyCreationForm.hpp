#pragma once
#include <iostream>
#include <fstream>
#include <string>

#include "Bureaucrat.hpp"
#include "AForm.hpp"

class Bureaucrat;

class ShrubberyCreationForm : public AForm
{
public:
    ShrubberyCreationForm();
    ShrubberyCreationForm(const std::string target);
    ShrubberyCreationForm(const ShrubberyCreationForm&);
    ShrubberyCreationForm& operator=(const ShrubberyCreationForm&);
    ~ShrubberyCreationForm();

    void	execute(Bureaucrat const & executor) const;

    class outfileNotOpenException : public std::exception
    {
    public:
        virtual const char *what() const throw();
    };

private:
    std::string target;

    void	writeTreesToFile(std::string filename) const;
};
