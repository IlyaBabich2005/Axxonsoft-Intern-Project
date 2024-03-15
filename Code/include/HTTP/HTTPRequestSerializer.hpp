#pragma once

#include "HTTPSerializer.hpp"
#include "HTTPRequest.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		class HTTPRequestSerializer : HTTPSerializer
		{
		public:
			std::vector<boost::asio::const_buffer> Serialize(std::shared_ptr<HTTPDocument> document) override;
		};
	}
}