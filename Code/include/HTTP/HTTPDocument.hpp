#pragma once

#include <vector>
#include <nlohmann/json.hpp>

#include "HTTPHeader.hpp"

using nlohmann::json,
	  std::vector;

namespace AxxonsoftInternProject
{
	namespace http
	{
		struct HTTPDocument
		{
			vector<HTTPHeader> headers;
			string version;
			string body;

			HTTPDocument();
			HTTPDocument(string version);
			
			virtual ~HTTPDocument();
		};
	}
}