#include "ATarget.hpp"

ATarget::ATarget()
{}

ATarget::ATarget(std::string const &type) : m_type(type)
{}

ATarget::ATarget(ATarget const &value)
{
	*this = value;
}

ATarget &ATarget::operator=(ATarget const &value)
{
	m_type = value.m_type;
	return *this;
}

ATarget::~ATarget()
{}

std::string const &ATarget::getType() const
{
	return m_type;
}

void ATarget::getHitBySpell(ASpell const &ref) const
{
	std::cout << m_type << " has been " << ref.getEffect() << "!\n";
}