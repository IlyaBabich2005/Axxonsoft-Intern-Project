#pragma once

#include "HTTPDocument.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		const std::string requestMethods[]
		{
			"GET",
			"POST",
			"DELETE"
		};

		enum ClientRequestType
		{
			deleteTarget = 0,
			downloadTarget,
			checkTarget,
			sendTarget
		};

		struct HTTPRequest : public HTTPDocument
		{
			std::string method;
			std::string uri;
			ClientRequestType type;
		};
	}
}