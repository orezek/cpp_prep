#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm() : AForm("RobotomyRequestForm", 72, 45)
{
	srand(time(0));
	target = "";
}

RobotomyRequestForm::RobotomyRequestForm(const std::string target) : AForm("RobotomyRequestForm", 72, 45), target(target)
{
	srand(time(0));
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& refObj) : AForm("RobotomyRequestForm", 72, 45)
{
	srand(time(0));
	this->target = refObj.target;
	*this = refObj;
}

RobotomyRequestForm& RobotomyRequestForm::operator=(const RobotomyRequestForm& refObj)
{
	if (this != &refObj)
		this->target = refObj.target;
	return (*this);
}

RobotomyRequestForm::~RobotomyRequestForm()
{}

void RobotomyRequestForm::execute(Bureaucrat const & executor) const
{
	if (this->getIsSigned() == false)
		throw AForm::NotSignedException();
	if (this->getGradeRequiredToExecute() < executor.getGrade())
		throw AForm::GradeTooLowException();

	std::cout << "*drilling noises* Wroom wroom" << std::endl;

	int randomValue = rand();

	if (randomValue % 2)
		std::cout << this->target << " has been robotomized successfully!" << std::endl;
	else
		std::cout << "Robotomy failed" << std::endl;
}