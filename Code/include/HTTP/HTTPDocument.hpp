#pragma once

#include <vector>

#include "HTTPHeader.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		struct HTTPDocument
		{
			std::vector<HTTPHeader> headers;
			std::string version;
			std::string body;

			HTTPDocument();
			HTTPDocument(std::string version);
			
			virtual ~HTTPDocument();
		};
	}
}