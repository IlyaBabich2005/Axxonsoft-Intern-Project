#include "HTTPRequestSerializer.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		std::vector<asio::const_buffer> HTTPRequestSerializer::Serialize(std::shared_ptr<HTTPDocument> document)
		{
			std::vector<asio::const_buffer> serializedHeadersAndBody = __super::Serialize(document);
			std::vector<asio::const_buffer> serializedDocument;

			serializedDocument.push_back(asio::buffer(std::dynamic_pointer_cast<HTTPRequest>(document)->method));
			serializedDocument.push_back(asio::buffer(separators::g_whiteSpaceSeparator));
			serializedDocument.push_back(asio::buffer(std::dynamic_pointer_cast<HTTPRequest>(document)->uri));
			serializedDocument.push_back(asio::buffer(separators::g_whiteSpaceSeparator));
			serializedDocument.push_back(asio::buffer(document->version));
			serializedDocument.push_back(asio::buffer(separators::g_httpDocumentLineSeparator));

			serializedDocument.insert(end(serializedDocument), begin(serializedHeadersAndBody), end(serializedHeadersAndBody));

			return serializedDocument;
		}
	}
}