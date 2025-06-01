
#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm() : AForm("PresidentialPardonForm", 25, 5)
{
    target = "";
}

PresidentialPardonForm::PresidentialPardonForm(const std::string target) : AForm("PresidentialPardonForm", 25, 5), target(target)
{}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm& refObj) : AForm("PresidentialPardonForm", 25, 5)
{
    this->target = refObj.target;
    *this = refObj;
}

PresidentialPardonForm& PresidentialPardonForm::operator=(const PresidentialPardonForm& refObj)
{
    if (this != &refObj)
        this->target = refObj.target;
    return (*this);
}

PresidentialPardonForm::~PresidentialPardonForm()
{}

void PresidentialPardonForm::execute(Bureaucrat const & executor) const
{
    if (this->getIsSigned() == false)
        throw AForm::NotSignedException();
    if (this->getGradeRequiredToExecute() < executor.getGrade())
        throw AForm::GradeTooLowException();
    std::cout << this->target << " has been pardoned by Zaphod Beeblebrox." << std::endl;
}