#pragma once

#include <boost/asio/buffer.hpp>
#include <memory>

#include "HTTPDocument.hpp"

namespace stock = AxxonsoftInternProject::http::stock;

using std::vector,
	  std::shared_ptr,
	  stock::characters::separators::headerNameValueSeparator,
	  stock::characters::separators::httpDocumentLineSeparator,
	  boost::asio::buffer,
	  boost::asio::const_buffer;

namespace AxxonsoftInternProject
{
	namespace http
	{
		class HTTPSerializer
		{
		private: 
			vector<const_buffer> SerializeHeaders(shared_ptr<HTTPDocument> document);

		public:
			virtual vector<const_buffer> Serialize(shared_ptr<HTTPDocument> document);
		};
	}
}