#pragma once

#include "HTTPDocument.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		struct HTTPReply : HTTPDocument
		{
			string code;
			string status;
		};
	}
}