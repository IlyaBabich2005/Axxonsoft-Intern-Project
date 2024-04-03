#pragma once

#include <string>
#include <vector>

#include "HTTPHeaderValueClassField.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		struct HTTPHeaderValueClass
		{
			std::string m_name;
			std::vector<HTTPHeaderValueClassField> m_fields;

			HTTPHeaderValueClass(std::string value);
			HTTPHeaderValueClass();
		};
	}
}