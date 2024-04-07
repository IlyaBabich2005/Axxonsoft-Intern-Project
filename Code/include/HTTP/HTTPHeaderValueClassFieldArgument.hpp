#pragma once

#include <string>

namespace AxxonsoftInternProject
{
	namespace http
	{
		struct HTTPHeaderValueClassFielsArgument
		{
			std::string m_value;
			bool m_isString = false;

			HTTPHeaderValueClassFielsArgument();
			HTTPHeaderValueClassFielsArgument(const std::string& value);
			HTTPHeaderValueClassFielsArgument(const std::string& value, const bool& isString);
		};
	}
}