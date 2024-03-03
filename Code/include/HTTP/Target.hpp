#pragma once

#include <vector>
#include <string>

using std::vector,
	  std::string;

namespace AxxonsoftInternProject
{
	namespace http
	{
		struct Target
		{
			vector<string> components;
			bool isFile = false;
		};
	}
}