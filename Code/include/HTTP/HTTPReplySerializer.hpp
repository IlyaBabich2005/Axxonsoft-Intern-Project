#pragma once

#include "HTTPSerializer.hpp"
#include "HTTPReply.hpp"

namespace separators = stock::characters::separators;
namespace asio = boost::asio;

namespace AxxonsoftInternProject
{
	namespace http
	{
		class HTTPReplySerializer : public HTTPSerializer
		{
		public:
			std::vector<asio::const_buffer> Serialize(std::shared_ptr<HTTPDocument> document) override;
		};
	}
}