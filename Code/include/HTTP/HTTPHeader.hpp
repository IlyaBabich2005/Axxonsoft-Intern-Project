#pragma once

#include <string>
#include "Stock.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		struct HTTPHeader
		{
			std::string m_name;
			std::string m_value;

			HTTPHeader();
			HTTPHeader(std::string name, std::string value);
		};
	}
}