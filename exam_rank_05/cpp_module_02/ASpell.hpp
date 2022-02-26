#pragma once
#include <iostream>
#include <string>
#include "ATarget.hpp"

class ATarget;

class ASpell
{
	private:
		std::string m_name;
		std::string m_effect;

	public:
		ASpell();
		ASpell(std::string const &name, std::string const &effect);
		ASpell(ASpell const &value);
		ASpell &operator=(ASpell const &value);
		~ASpell();

		std::string const &getName() const;
		std::string const &getEffect() const;

		virtual ASpell *clone() const = 0;
		void launch(ATarget const &ref) const;
};