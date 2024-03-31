#pragma once

#include <string>
#include <vector>

namespace AxxonsoftInternProject
{
	namespace http
	{
		struct HTTPHeaderValueClass
		{
			std::string m_name;
			std::vector<std::string> m_arguments;

			HTTPHeaderValueClass(std::string value);
			HTTPHeaderValueClass();
		};
	}
}