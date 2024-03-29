#pragma once

#include <string>
#include <vector>

#include "Stock.hpp"
#include "HTTPHeaderField.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		struct HTTPHeader
		{
			std::string m_name;
			std::vector<HTTPHeaderField> m_values;

			HTTPHeader();
			HTTPHeader(std::string name, std::string value);
		};
	}
} 