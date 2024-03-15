#pragma once

#include <boost/asio/buffer.hpp>
#include <memory>

#include "HTTPDocument.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		class HTTPSerializer
		{
		private: 
			std::vector<boost::asio::const_buffer> serializeHeaders(std::shared_ptr<HTTPDocument> document);
			boost::asio::const_buffer serializeBody(std::shared_ptr<HTTPDocument> document);

		public:
			virtual std::vector<boost::asio::const_buffer> Serialize(std::shared_ptr<HTTPDocument> document);
		};
	}
}