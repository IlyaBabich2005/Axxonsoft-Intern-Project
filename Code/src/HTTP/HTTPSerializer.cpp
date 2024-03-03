#include "HTTPSerializer.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		vector<const_buffer> HTTPSerializer::SerializeHeaders(shared_ptr<HTTPDocument> document)
		{
			vector<const_buffer> serializedHeaders;

			for (int i = 0; i < document->headers.size(); i++)
			{
				serializedHeaders.push_back(buffer(document->headers[i].name));
				serializedHeaders.push_back(buffer(headerNameValueSeparator));
				serializedHeaders.push_back(buffer(document->headers[i].value));
				serializedHeaders.push_back(buffer(httpDocumentLineSeparator));
			}

			serializedHeaders.push_back(buffer(httpDocumentLineSeparator));

			return serializedHeaders;
		}

		const_buffer HTTPSerializer::SerializeBody(shared_ptr<HTTPDocument> document)
		{
			return buffer(document->body);
		}

		vector<const_buffer> HTTPSerializer::Serialize(shared_ptr<HTTPDocument> document)
		{
			vector<const_buffer> serializedDocument = this->SerializeHeaders(document);

			if (document->body.size() > 0)
			{
				serializedDocument.push_back(this->SerializeBody(document));
			}

			return serializedDocument;
		}
	}
}