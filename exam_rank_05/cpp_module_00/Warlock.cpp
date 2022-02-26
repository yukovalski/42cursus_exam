#include "Warlock.hpp"

Warlock::Warlock( )
{}

Warlock::Warlock( std::string const name, std::string const title )  : m_name(name), m_title(title)
{
    std::cout << m_name << ": This looks like another boring day." << std::endl;
}

Warlock::~Warlock( )
{
    std::cout << m_name << ": My job here is done!" << std::endl;
}

std::string const &Warlock::getName() const
{
    return m_name;
}

std::string const &Warlock::getTitle() const
{
    return m_title;
}

void        Warlock::setTitle( std::string value )
{
    m_title = value;
}

void        Warlock::introduce() const
{
    std::cout << m_name << ": I am " << m_name << ", " << m_title << "!" << std::endl;
}