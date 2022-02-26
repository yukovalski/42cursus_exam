#ifndef ATARGET
#define ATARGET

#include <iostream>
#include <string>
#include "ASpell.hpp"

class ASpell;

class ATarget
{
private:
    std::string m_type;
public:
    ATarget(/* args */);
    ATarget(std::string const &type);
    ATarget(ATarget const &value);
    ATarget &operator=(ATarget const &value);
    ~ATarget();

    std::string const &getType() const;
    virtual ATarget *clone() const = 0;
    void getHitBySpell(ASpell const &value) const;
};


#endif //ATARGET
