#include "ASpell.hpp"

ASpell::ASpell()
{}

ASpell::ASpell(std::string const &name, std::string const &effect) : m_name(name), m_effect(effect)
{}

ASpell::ASpell(ASpell const &value)
{
	*this = value;
}

ASpell &ASpell::operator=(ASpell const &value)
{
	m_name = value.m_name;
	m_effect = value.m_effect;
	return *this;
}
ASpell::~ASpell()
{}

std::string const &ASpell::getName() const
{
	return m_name;
}

std::string const &ASpell::getEffect() const
{
	return m_effect;
}

void ASpell::launch(ATarget const &ref) const
{
	ref.getHitBySpell(*this);
}