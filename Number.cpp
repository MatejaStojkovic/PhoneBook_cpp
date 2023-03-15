#include "Number.h"

std::ostream& operator<<(std::ostream& os, const Number& n)
{
	return os << n.number;
}

void Number::setNumber(const std::string& number)
{
	this->number = number;
}
