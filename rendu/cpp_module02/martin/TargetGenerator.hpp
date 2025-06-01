#pragma once

#include <string>
#include <iostream>
#include <vector>

#include "ATarget.hpp"

class TargetGenerator
{
	public:
		TargetGenerator();
		~TargetGenerator();
		void learnTargetType(ATarget*); //, that COPIES a TargetType in the book
		void forgetTargetType(std::string const &); //, that deletes a TargetType from the book, except if it isn't there
		ATarget* createTarget(std::string const &); //, that receives a string corresponding to the name of a TargetType, creates it, and returns it.


	private:
		std::vector<ATarget*> targets;
		TargetGenerator(const TargetGenerator&);
		TargetGenerator& operator=(const TargetGenerator&);
};