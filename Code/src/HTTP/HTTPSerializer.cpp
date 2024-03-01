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
				serializedHeaders.push_back(buffer(document->headers[0].name));
				serializedHeaders.push_back(buffer(headerNameValueSeparator));
				serializedHeaders.push_back(buffer(document->headers[0].value));
				serializedHeaders.push_back(buffer(httpDocumentLineSeparator));
			}

			serializedHeaders.push_back(buffer(httpDocumentLineSeparator));

			return serializedHeaders;
		}

		vector<const_buffer> HTTPSerializer::Serialize(shared_ptr<HTTPDocument> document)
		{
			return this->SerializeHeaders(document);
		}
	}
}