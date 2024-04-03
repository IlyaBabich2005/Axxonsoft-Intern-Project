#pragma once

#include <string>
#include <vector>

namespace AxxonsoftInternProject
{
	namespace http
	{
		struct HTTPHeaderValueClassField
		{
			std::string m_name;
			std::vector<std::string> m_arguments;

			HTTPHeaderValueClassField();
			HTTPHeaderValueClassField(std::string value);
			HTTPHeaderValueClassField(std::string name, std::string value);
		};
	}
}