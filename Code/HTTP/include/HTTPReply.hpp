#pragma once

#include "HTTPDocument.hpp"

namespace http
{
	struct HTTPReply : HTTPDocument
	{
		string method;
		string uri;
	};
}