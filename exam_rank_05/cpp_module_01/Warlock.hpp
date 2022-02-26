#ifndef WARLOCK_HPP
#define WARLOCK_HPP

#include "ASpell.hpp"
#include "ATarget.hpp"
#include <map>

class Warlock
{
private:
    std::string m_name;
    std::string m_title;
    std::map<std::string, ASpell *> arr;
public:
    Warlock(/* args */);
    Warlock(std::string const &name, std::string const &title);
    Warlock(Warlock const &value);
    Warlock &operator=(Warlock const &value);
    ~Warlock();

    std::string const &getName() const;
    std::string const &getTitle() const;

    void introduce();
    void learnSpell(ASpell *value);
    void launchSpell(std::string const &name, ATarget &value);
    void forgetSpell(std::string const &name);

};


#endif //WARLOCK_HPP
