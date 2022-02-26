#include "Dummy.hpp"

Dummy::Dummy(/* args */) : ATarget("Target Practice Dummy")
{}

Dummy::~Dummy()
{}

ATarget *Dummy::clone() const
{
    return (new Dummy());
}