#pragma once

#include "HTTPSerializer.hpp"
#include "HTTPReply.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		class HTTPReplySerializer : public HTTPSerializer
		{
		public:
			std::vector<boost::asio::const_buffer> Serialize(std::shared_ptr<HTTPDocument> document) override;
		};
	}
}