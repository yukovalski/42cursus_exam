#ifndef ASPELL_HPP
#define ASPELL_HPP
#include <iostream>
#include <string>
#include "ATarget.hpp"

class ATarget;

class ASpell
{
private:
    std::string m_name;
    std::string m_effects;

public:
    ASpell();
    ASpell(const std::string name, const std::string effects);
    ASpell(ASpell const &value);
    ASpell &operator=(ASpell const &value);
    virtual ~ASpell();

    std::string const &getName() const;
    std::string const &getEffects() const;

    virtual ASpell *clone() const = 0;
    void launch(ATarget const &value) const;
};

#endif //ASPELL_HPP
