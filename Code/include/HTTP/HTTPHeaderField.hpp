#pragma once

#include <string>

namespace AxxonsoftInternProject
{
	namespace http
	{
		struct HTTPHeaderField
		{
			std::string m_name;
			std::string m_value;

			HTTPHeaderField(std::string value);
			HTTPHeaderField();
		};
	}
}