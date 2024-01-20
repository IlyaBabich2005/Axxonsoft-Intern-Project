#pragma once

#include "HTTPDocument.hpp"

namespace http
{
	struct HTTPRequest : HTTPDocument
	{
		string method;
		string uri;
	};
}