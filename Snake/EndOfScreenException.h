#pragma once
#include <stdexcept>

class EndOfScreenException : public std::logic_error
{
public:
	void* customDataForNextScreen;
	EndOfScreenException(void* data) : std::logic_error("This screen should be changed.") {
		customDataForNextScreen = data;
	}
};

