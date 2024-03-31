#pragma once

#include <string>

#include "Stock.hpp"
#include "HTTPHeaderValueClass.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		struct HTTPHeader
		{
			std::string m_name;
			std::vector<HTTPHeaderValueClass> m_values;

			HTTPHeader();
			HTTPHeader(std::string name, std::string value);
		};
	}
} 