#pragma once

#include <vector>

#include "HTTPHeader.hpp"

using std::vector;

namespace http
{
	struct HTTPDocument
	{
		vector<HTTPHeader> headers;
		string version;
	};
}