#pragma once

#include <vector>

#include "HTTPHeaderValueClassFieldArgument.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		struct HTTPHeaderValueClassField
		{
			std::string m_name;
			std::vector<HTTPHeaderValueClassFielsArgument> m_arguments;

			HTTPHeaderValueClassField();
			HTTPHeaderValueClassField(std::string value);
			HTTPHeaderValueClassField(std::string name, std::string value);
			HTTPHeaderValueClassField(std::string name, HTTPHeaderValueClassFielsArgument argument);
		};
	}
}