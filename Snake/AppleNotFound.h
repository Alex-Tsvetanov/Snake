#pragma once
#include <stdexcept>

class AppleNotFound : public std::logic_error
{
public:
	AppleNotFound() : std::logic_error("There is no apple at that point.") {}
};

