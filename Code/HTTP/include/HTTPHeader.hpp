#pragma once

#include <string>

using std::string;

namespace http
{
	struct HTTPHeader
	{
		string name;
		string value;
	};
}