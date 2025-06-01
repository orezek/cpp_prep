#pragma once

#include <string>
#include <iostream>

#include "ASpell.hpp"

class ASpell;

class ATarget
{
	public:
		ATarget(std::string type);
		ATarget(const ATarget&);
		ATarget& operator=(const ATarget&);
		const std::string& getType() const;
		virtual ~ATarget();
		virtual ATarget* clone() = 0;
		void getHitBySpell(const ASpell& spell) const;

	private:
		std::string type;
};