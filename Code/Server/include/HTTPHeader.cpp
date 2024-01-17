#include "HTTPHeader.hpp"

namespace http
{
	Header::Header(string name, string value) :
		name{name},
		value{value}
	{
	}

	string Header::ToString()
	{
		return this->name + ": " + this->value;
	}
}