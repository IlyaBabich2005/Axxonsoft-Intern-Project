#include "HTTPReplySerializer.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		std::vector<boost::asio::const_buffer> HTTPReplySerializer::Serialize(std::shared_ptr<HTTPDocument> document)
		{
			std::vector<boost::asio::const_buffer> serializedHeadersAndBody = __super::Serialize(document);
			std::vector<boost::asio::const_buffer> serializedDocument;

			serializedDocument.push_back(boost::asio::buffer(document->m_version));
			serializedDocument.push_back(boost::asio::buffer(stock::characters::separators::g_whiteSpaceSeparator));
			serializedDocument.push_back(boost::asio::buffer(std::dynamic_pointer_cast<HTTPReply>(document)->m_status));
			serializedDocument.push_back(boost::asio::buffer(stock::characters::separators::g_httpDocumentLineSeparator));

			serializedDocument.insert(end(serializedDocument), begin(serializedHeadersAndBody), end(serializedHeadersAndBody));

			return serializedDocument;
		}
	}
}