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
			std::string m_method;
			std::string m_uri;
			ClientRequestType m_type;
		};
	}
}