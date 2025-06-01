#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm() : AForm("ShrubberyCreationForm", 145, 137)
{
	target = "";
}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string target) : AForm("ShrubberyCreationForm", 145, 137), target(target)
{}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& refObj) : AForm("ShrubberyCreationForm", 145, 137)
{
	this->target = refObj.target;
	*this = refObj;
}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& refObj)
{
	if (this != &refObj)
		this->target = refObj.target;
	return (*this);
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{}


void	ShrubberyCreationForm::writeTreesToFile(std::string filename) const
{
	std::ofstream outFile;

	outFile.open(filename.c_str(), std::ios::out);
	if (!outFile.is_open())
	{
		throw outfileNotOpenException();
		return;
	}

	outFile << "ASCII TREE1!\n" << std::endl;
	outFile << "RANDOM FOLDER1/" << std::endl;
	outFile << "├─ random dir 1/" << std::endl;
	outFile << "├─ random dir 2/" << std::endl;
	outFile << "│  ├─ random_file.txt" << std::endl;
	outFile << "│  ├─ random_file.ico" << std::endl;
	outFile << "│  ├─ random_file.html" << std::endl;
	outFile << "├─ random dir 3/" << std::endl;
	outFile << "│  ├─ random_file.css" << std::endl;
	outFile << "│  ├─ random_file.js" << std::endl;
	outFile << std::endl;

	outFile << "ASCII TREE2!\n" << std::endl;
	outFile << "RANDOM FOLDER2/" << std::endl;
	outFile << "├─ random dir 1/" << std::endl;
	outFile << "│  ├─ random_file.txt" << std::endl;
	outFile << "│  ├─ random_file.html" << std::endl;
	outFile << "├─ random dir 2/" << std::endl;
	outFile << "│  ├─ random_file.css" << std::endl;
	outFile << "│  ├─ random_file.js" << std::endl;
	outFile << "├─ random dir 3/" << std::endl;
	outFile << std::endl;

	outFile << "ASCII ART TREES!" << std::endl;

	for (int i = 0; i < 3; i++)
	{
		outFile << "         $" << std::endl;
		outFile << "        d$b" << std::endl;
		outFile << "      .d$$$b." << std::endl;
		outFile << "    .d$i$$$$$b." << std::endl;
		outFile << "      d$$i$$b" << std::endl;
		outFile << "     d$$$$$@$b" << std::endl;
		outFile << "  .d$@$$$$$$$$@b." << std::endl;
		outFile << ".d$$$$i$$$$$$$$$$b." << std::endl;
		outFile << "        ###" << std::endl;
		outFile << "        ###" << std::endl;
		outFile << std::endl;
	}
	outFile.close();
}

void ShrubberyCreationForm::execute(Bureaucrat const & executor) const
{
	if (this->getIsSigned() == false)
		throw AForm::NotSignedException();
	if (this->getGradeRequiredToExecute() < executor.getGrade())
		throw AForm::GradeTooLowException();

	std::string filename;

	filename = target + "_shrubbery";
	this->writeTreesToFile(filename);
}

const char *ShrubberyCreationForm::outfileNotOpenException::what(void) const throw()
{
	return ("Cannot open file.");
}