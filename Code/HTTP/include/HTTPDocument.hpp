#pragma once

#include <vector>
#include <map>
#include <boost/json/value.hpp>

#include "HTTPHeader.hpp"

using std::vector,
	  std::map,
	  boost::json::value;

namespace http
{
	struct HTTPDocument
	{
		map<string, value> body;
		vector<HTTPHeader> headers;
		string version;
	};
}