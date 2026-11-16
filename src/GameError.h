#pragma once
#include <stdexcept>
#include <string>

using namespace std;

class GameError : public logic_error
{
public:

	using logic_error::logic_error;

};

