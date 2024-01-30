#pragma once

#include "HTTPDocument.hpp"

namespace http
{
	struct HTTPReply : HTTPDocument
	{
		string code;
		string status;
	};
}