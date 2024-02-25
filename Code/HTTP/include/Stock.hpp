#pragma once

#include <string>

#include "HTTPReplyStatus.hpp"

using std::string;

namespace AxxonsoftInternProject
{
	namespace http
	{
		namespace stock
		{
			namespace characters
			{
				namespace separators
				{
					const string whiteSpaceSeparator = " ";
					const string headerNameValueSeparator = ": ";
					const string httpDocumentLineSeparator = "\r\n";
				}
			}

			namespace replyStatuses
			{
				const string badRequest { "400 BadRequest" };
				const string ok{ "200 OK" };
			}
		}
	}
}