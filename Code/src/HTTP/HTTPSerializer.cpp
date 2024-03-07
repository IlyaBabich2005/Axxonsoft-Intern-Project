#include "HTTPSerializer.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		vector<const_buffer> HTTPSerializer::serializeHeaders(shared_ptr<HTTPDocument> document)
		{
			vector<const_buffer> serializedHeaders;

			for (int i = 0; i < document->headers.size(); i++)
			{
				serializedHeaders.push_back(buffer(document->headers[i].name));
				serializedHeaders.push_back(buffer(g_headerNameValueSeparator));
				serializedHeaders.push_back(buffer(document->headers[i].value));
				serializedHeaders.push_back(buffer(g_httpDocumentLineSeparator));
			}

			serializedHeaders.push_back(buffer(g_httpDocumentLineSeparator));

			return serializedHeaders;
		}

		const_buffer HTTPSerializer::serializeBody(shared_ptr<HTTPDocument> document)
		{
			return buffer(document->body);
		}

		vector<const_buffer> HTTPSerializer::Serialize(shared_ptr<HTTPDocument> document)
		{
			vector<const_buffer> serializedDocument = this->serializeHeaders(document);

			if (document->body.size() > 0)
			{
				serializedDocument.push_back(serializeBody(document));
			}

			return serializedDocument;
		}
	}
}