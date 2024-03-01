#pragma once

#include <string>
#include "Stock.hpp"

namespace stock = AxxonsoftInternProject::http::stock;

using stock::characters::separators::headerNameValueSeparator,
	  std::string;

namespace AxxonsoftInternProject
{
	namespace http
	{
		struct HTTPHeader
		{
			string name;
			string value;

			HTTPHeader();
			HTTPHeader(string name, string value);
		};
	}
}