#pragma once

#include "HTTPDocument.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		struct HTTPReply : public HTTPDocument
		{
			string status;

			HTTPReply();
			HTTPReply(string version, string status);
		};

		namespace stock
		{
			namespace replyes
			{
				const HTTPReply badRequest{ string{"HTTP/1.0"}, stock::replyStatuses::badRequest };
			}
		}
	}
}