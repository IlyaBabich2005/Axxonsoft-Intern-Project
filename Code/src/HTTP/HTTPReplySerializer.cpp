#include "HTTPReplySerializer.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		vector<const_buffer> HTTPReplySerializer::Serialize(shared_ptr<HTTPDocument> document)
		{
			vector<const_buffer> serializedHeadersAndBody = __super::Serialize(document);
			vector<const_buffer> serializedDocument;

			serializedDocument.push_back(buffer(document->version));
			serializedDocument.push_back(buffer(whiteSpaceSeparator));
			serializedDocument.push_back(buffer(dynamic_pointer_cast<HTTPReply>(document)->status));
			serializedDocument.push_back(buffer(httpDocumentLineSeparator));

			serializedDocument.insert(end(serializedDocument), begin(serializedHeadersAndBody), end(serializedHeadersAndBody));

			return serializedDocument;
		}
	}
}