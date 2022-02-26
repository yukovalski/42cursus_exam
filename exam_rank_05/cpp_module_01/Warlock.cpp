#include "Warlock.hpp"

Warlock::Warlock()
{}

Warlock::Warlock(std::string const &name, std::string const &title) : m_name(name), m_title(title)
{
    std::cout << m_name << ": This looks like another boring day." << std::endl;
}

Warlock::~Warlock()
{
    std::cout << m_name << ": My job here is done!" << std::endl;
}

Warlock::Warlock(Warlock const &value)
{
    *this = value;
}

Warlock &Warlock::operator=(Warlock const &value)
{
    m_name = value.m_name;
    m_title = value.m_title;
    return *this;
}

std::string const &Warlock::getName() const
{
    return m_name;
}

std::string const &Warlock::getTitle() const
{
    return m_title;
}

void Warlock::introduce()
{
    std::cout << m_name << ": I am " << m_name << ", " << m_title << "!" << std::endl;
}

void Warlock::learnSpell(ASpell *value)
{
    if (value)
        arr.insert(std::pair<std::string, ASpell *>(value->getName(), value->clone()));
}

void Warlock::launchSpell(std::string const &name, ATarget &value)
{
     ASpell* spell = arr[name];
        if (spell)
            spell->launch(value);

}

void Warlock::forgetSpell(std::string const &name)
{
    std::map<std::string, ASpell *>::iterator it = arr.find(name);
    if (it != arr.end())
        delete it->second;
    arr.erase(name);

}