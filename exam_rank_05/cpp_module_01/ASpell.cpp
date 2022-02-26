#include "ASpell.hpp"

ASpell::ASpell()
{}

ASpell::ASpell(const std::string name, const std::string effects) : m_name(name), m_effects(effects)
{}

ASpell::ASpell(ASpell const &value) 
{
    *this = value;
}

ASpell &ASpell::operator=(ASpell const &value)
{
    m_name = value.m_name;
    m_effects = value.m_effects;

    return *this;
}

ASpell::~ASpell()
{}

std::string const &ASpell::getName() const
{
    return m_name;
}

std::string const &ASpell::getEffects() const
{
    return m_effects;
}

void ASpell::launch(ATarget const &value) const
{
    value.getHitBySpell((*this));
}