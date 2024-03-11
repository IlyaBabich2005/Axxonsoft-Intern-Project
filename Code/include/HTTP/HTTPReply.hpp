#pragma once

#include "HTTPDocument.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		struct HTTPReply : public HTTPDocument
		{
			std::string status;

			HTTPReply();
			HTTPReply(std::string version, std::string status);
		};

		namespace stock
		{
			namespace replyes
			{
				const HTTPReply g_badRequest{ std::string{"HTTP/1.0"}, stock::replyStatuses::g_badRequest};
			}
		}
	}
}