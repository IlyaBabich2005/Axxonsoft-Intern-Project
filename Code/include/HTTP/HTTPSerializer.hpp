#pragma once

#include <boost/asio/buffer.hpp>
#include <memory>

#include "HTTPDocument.hpp"

namespace stock = AxxonsoftInternProject::http::stock;

using std::vector,
	  std::shared_ptr,
	  stock::characters::separators::g_headerNameValueSeparator,
	  stock::characters::separators::g_httpDocumentLineSeparator,
	  boost::asio::buffer,
	  boost::asio::const_buffer;

namespace AxxonsoftInternProject
{
	namespace http
	{
		class HTTPSerializer
		{
		private: 
			vector<const_buffer> serializeHeaders(shared_ptr<HTTPDocument> document);
			const_buffer serializeBody(shared_ptr<HTTPDocument> document);

		public:
			virtual vector<const_buffer> Serialize(shared_ptr<HTTPDocument> document);
		};
	}
}