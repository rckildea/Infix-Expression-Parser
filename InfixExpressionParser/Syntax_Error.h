#pragma once
#include <stdexcept>

class Syntax_Error : public std::invalid_argument {
public:
	Syntax_Error(std::string msg) : std::invalid_argument(msg) {}
};