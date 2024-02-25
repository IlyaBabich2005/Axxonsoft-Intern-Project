#include "HTTPReply.hpp"

AxxonsoftInternProject::http::HTTPReply::HTTPReply()
{
}

vector<const_buffer> AxxonsoftInternProject::http::HTTPReply::Serialize()
{
	vector<const_buffer> serializedReply;
	vector<const_buffer> serializedVersion = this->SerializeVersion();
	vector<const_buffer> serializedHeadersAndBody = __super::Serialize();


	serializedReply.insert(end(serializedReply), begin(serializedVersion), end(serializedVersion));
	serializedReply.push_back(buffer(whiteSpaceSeparator));
	serializedReply.push_back(buffer(this->status));
	serializedReply.push_back(buffer(httpDocumentLineSeparator));
	serializedReply.insert(end(serializedReply), begin(serializedHeadersAndBody), end(serializedHeadersAndBody));

	return serializedReply;
}