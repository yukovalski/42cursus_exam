#pragma once

#include "ASpell.hpp"
#include <map>

class SpellBook
{
private:
	std::map<std::string, ASpell*> arr;
	
public:
	SpellBook();
	SpellBook(SpellBook const &value);
	SpellBook &operator=(SpellBook const &value);
	~SpellBook();

	void learnSpell(ASpell *val);
	void forgetSpell(std::string const &val);
	ASpell* createSpell(std::string const &val);

};