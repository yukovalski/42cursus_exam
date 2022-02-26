#ifndef FWOOSH_HPP
#define FWOOSH_HPP

#include "ASpell.hpp"

class Fwoosh: public ASpell
{
private:
    /* data */
public:
    Fwoosh(/* args */);
    ~Fwoosh();

    virtual ASpell *clone() const;
};


#endif // FWOOSH_HPP
