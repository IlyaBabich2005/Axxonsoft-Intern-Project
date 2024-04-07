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
			std::vector<HTTPHeaderValueClass> m_classes;

			HTTPHeader();
			HTTPHeader(std::string name);
			HTTPHeader(std::string name, std::string value);
		};
	}
} 