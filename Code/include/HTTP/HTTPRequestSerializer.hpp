#pragma once

#include "HTTPSerializer.hpp"
#include "HTTPRequest.hpp"

namespace separators = stock::characters::separators;

namespace AxxonsoftInternProject
{
	namespace http
	{
		class HTTPRequestSerializer : HTTPSerializer
		{
		public:
			std::vector<asio::const_buffer> Serialize(std::shared_ptr<HTTPDocument> document) override;
		};
	}
}