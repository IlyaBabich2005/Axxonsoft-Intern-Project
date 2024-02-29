#pragma once

#include "HTTPDocument.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		struct HTTPReply : public HTTPDocument
		{
			string code;
			string status;
		};
	}
}