#pragma once

#include <boost/asio/buffer.hpp>
#include <memory>

#include "HTTPDocument.hpp"

namespace stock = AxxonsoftInternProject::http::stock;
namespace separators = stock::characters::separators;
namespace asio = boost::asio;

namespace AxxonsoftInternProject
{
	namespace http
	{
		class HTTPSerializer
		{
		private: 
			std::vector<asio::const_buffer> serializeHeaders(std::shared_ptr<HTTPDocument> document);
			asio::const_buffer serializeBody(std::shared_ptr<HTTPDocument> document);

		public:
			virtual std::vector<asio::const_buffer> Serialize(std::shared_ptr<HTTPDocument> document);
		};
	}
}