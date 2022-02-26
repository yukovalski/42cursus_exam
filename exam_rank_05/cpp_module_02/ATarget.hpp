#pragma once
#include <iostream>
#include <string>
#include "ASpell.hpp"

class ASpell;

class ATarget
{
	private:
		std::string m_type;

	public:
		ATarget();
		ATarget(std::string const &type);
		ATarget(ATarget const &value);
		ATarget &operator=(ATarget const &value);
		~ATarget();

		std::string const &getType() const;
		void getHitBySpell(ASpell const &ref) const;
		virtual ATarget *clone() const = 0;
};