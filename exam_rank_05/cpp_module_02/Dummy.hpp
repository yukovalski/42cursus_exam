#pragma once
#include "ATarget.hpp"

class Dummy : public ATarget
{
	Dummy();
	~Dummy();
	ATarget *clone() const;
};
