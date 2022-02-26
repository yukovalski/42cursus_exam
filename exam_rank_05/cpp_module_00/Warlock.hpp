#pragma once

#include <iostream>
#include <string>
#include <cstdlib>

class Warlock {

private:
    std::string     m_name;
    std::string     m_title;
    
    Warlock ( );
    Warlock ( Warlock const &value );
    Warlock         operator=(Warlock const &value);

public:
    Warlock ( std::string const name, std::string const string );
    virtual ~Warlock( );

    std::string     const &getName() const;
    std::string     const &getTitle() const;
    void            setTitle( std::string value );
    void            introduce() const;

};
