#pragma once

#include <string>
#include "Stock.hpp"

namespace stock = AxxonsoftInternProject::http::stock;

namespace separators = stock::characters::separators;

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