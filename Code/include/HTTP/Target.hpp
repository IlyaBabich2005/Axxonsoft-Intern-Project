#pragma once

#include <vector>
#include <string>

namespace AxxonsoftInternProject
{
	namespace http
	{
		struct Target
		{
			std::vector<std::string> components;
			bool isFile = false;
		};
	}
}