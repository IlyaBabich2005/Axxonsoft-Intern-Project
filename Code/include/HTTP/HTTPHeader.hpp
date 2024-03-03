#pragma once

#include <string>
#include "Stock.hpp"

namespace stock = AxxonsoftInternProject::http::stock;

using stock::characters::separators::headerNameValueSeparator;

using std::string;

namespace AxxonsoftInternProject
{
	namespace http
	{
		struct HTTPHeader
		{
			std::string name;
			std::string value;

			HTTPHeader();
			HTTPHeader(std::string name, std::string value);
		};
	}
}