#include "HTTPDocument.hpp"

vector<const_buffer> AxxonsoftInternProject::http::HTTPDocument::SerializeVersion()
{
	vector<const_buffer> serializedVersion;

	serializedVersion.push_back(buffer(this->version));
}

vector<const_buffer> AxxonsoftInternProject::http::HTTPDocument::SerializeHeaders()
{
	vector<const_buffer> serializedHeaders;

	for (auto header : this->headers)
	{
		vector<const_buffer> serializedHeader = header.Serialize();
		serializedHeaders.insert(end(serializedHeaders), begin(serializedHeader), end(serializedHeader));
		serializedHeaders.push_back(buffer(httpDocumentLineSeparator));
	}

	serializedHeaders.push_back(buffer(httpDocumentLineSeparator));
}

vector<const_buffer> AxxonsoftInternProject::http::HTTPDocument::SerializeBody()
{
	return vector<const_buffer>();
}

vector<const_buffer> AxxonsoftInternProject::http::HTTPDocument::Serialize()
{
	this->SerializeHeaders();
	//his->SerializeBody();
}
