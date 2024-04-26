#pragma once
#include <stdexcept>

class DeadSnake : public std::logic_error
{
public:
	DeadSnake() : std::logic_error("The snake ate itself and died.") {}
};

