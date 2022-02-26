#pragma once
#include "ASpell.hpp"

class Fireball : public ASpell
{
	Fireball();
	~Fireball();
	ASpell *clone() const;
};
