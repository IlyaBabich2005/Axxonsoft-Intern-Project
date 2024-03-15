#include "HTTPRequestSerializer.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		std::vector<boost::asio::const_buffer> HTTPRequestSerializer::Serialize(std::shared_ptr<HTTPDocument> document)
		{
			std::vector<boost::asio::const_buffer> serializedHeadersAndBody = __super::Serialize(document);
			std::vector<boost::asio::const_buffer> serializedDocument;

			serializedDocument.push_back(boost::asio::buffer(std::dynamic_pointer_cast<HTTPRequest>(document)->m_method));
			serializedDocument.push_back(boost::asio::buffer(stock::characters::separators::g_whiteSpaceSeparator));
			serializedDocument.push_back(boost::asio::buffer(std::dynamic_pointer_cast<HTTPRequest>(document)->m_uri));
			serializedDocument.push_back(boost::asio::buffer(stock::characters::separators::g_whiteSpaceSeparator));
			serializedDocument.push_back(boost::asio::buffer(document->m_version));
			serializedDocument.push_back(boost::asio::buffer(stock::characters::separators::g_httpDocumentLineSeparator));

			serializedDocument.insert(end(serializedDocument), begin(serializedHeadersAndBody), end(serializedHeadersAndBody));

			return serializedDocument;
		}
	}
}