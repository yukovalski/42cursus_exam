

#include "SpellBook.hpp"

SpellBook::SpellBook()
{}

SpellBook::SpellBook(SpellBook const &value)
{}

SpellBook &SpellBook::operator=(SpellBook const &value)
{}

SpellBook::~SpellBook()
{
	
}

void SpellBook::learnSpell(ASpell *val)
{
	if (val)
		arr.insert(std::pair<std::string, ASpell *>(val->getName(), val->clone()));
}

void SpellBook::forgetSpell(std::string const &val)
{
	std::map<std::string, ASpell *>::iterator it = arr.find(val);
	if ( it != arr.end())
		delete it->second;
	arr.erase(val);
}

ASpell *SpellBook::createSpell(std::string const &val)
{
	std::map<std::string, ASpell *>::iterator it = arr.find(val);
	if ( it != arr.end())
		return arr[val];
	return NULL;
}
