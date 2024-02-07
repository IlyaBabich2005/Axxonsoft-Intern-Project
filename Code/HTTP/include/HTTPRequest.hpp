#pragma once

#include "HTTPDocument.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		struct HTTPRequest : HTTPDocument
		{
			string method;
			string uri;
		};
	}
}