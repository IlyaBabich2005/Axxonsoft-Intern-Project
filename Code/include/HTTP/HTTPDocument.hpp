#pragma once

#include <vector>

#include "HTTPHeader.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		struct HTTPDocument
		{
			std::vector<HTTPHeader> m_headers;
			std::string m_version;
			std::string m_body;

			HTTPDocument();
			HTTPDocument(std::string version);
			
			virtual ~HTTPDocument();
		};
	}
}