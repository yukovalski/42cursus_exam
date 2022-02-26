#pragma once
#include "ATarget.hpp"

class BrickWall : public ATarget
{
	BrickWall();
	~BrickWall();
	ATarget *clone() const;
};
