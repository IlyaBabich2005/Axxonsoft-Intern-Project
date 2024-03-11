#include "HTTPSerializer.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		std::vector<asio::const_buffer> HTTPSerializer::serializeHeaders(std::shared_ptr<HTTPDocument> document)
		{
			std::vector<asio::const_buffer> serializedHeaders;

			for (int i = 0; i < document->headers.size(); i++)
			{
				serializedHeaders.push_back(asio::buffer(document->headers[i].name));
				serializedHeaders.push_back(asio::buffer(separators::g_headerNameValueSeparator));
				serializedHeaders.push_back(asio::buffer(document->headers[i].value));
				serializedHeaders.push_back(asio::buffer(separators::g_httpDocumentLineSeparator));
			}

			serializedHeaders.push_back(asio::buffer(separators::g_httpDocumentLineSeparator));

			return serializedHeaders;
		}

		asio::const_buffer HTTPSerializer::serializeBody(std::shared_ptr<HTTPDocument> document)
		{
			return asio::buffer(document->body);
		}

		std::vector<asio::const_buffer> HTTPSerializer::Serialize(std::shared_ptr<HTTPDocument> document)
		{
			std::vector<asio::const_buffer> serializedDocument = this->serializeHeaders(document);

			if (document->body.size() > 0)
			{
				serializedDocument.push_back(serializeBody(document));
			}

			return serializedDocument;
		}
	}
}