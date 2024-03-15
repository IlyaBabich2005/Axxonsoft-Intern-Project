#include "HTTPSerializer.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		std::vector<boost::asio::const_buffer> HTTPSerializer::serializeHeaders(std::shared_ptr<HTTPDocument> document)
		{
			std::vector<boost::asio::const_buffer> serializedHeaders;

			for (int i = 0; i < document->m_headers.size(); i++)
			{
				serializedHeaders.push_back(boost::asio::buffer(document->m_headers[i].m_name));
				serializedHeaders.push_back(boost::asio::buffer(stock::characters::separators::g_headerNameValueSeparator));
				serializedHeaders.push_back(boost::asio::buffer(document->m_headers[i].m_value));
				serializedHeaders.push_back(boost::asio::buffer(stock::characters::separators::g_httpDocumentLineSeparator));
			}

			serializedHeaders.push_back(boost::asio::buffer(stock::characters::separators::g_httpDocumentLineSeparator));

			return serializedHeaders;
		}

		boost::asio::const_buffer HTTPSerializer::serializeBody(std::shared_ptr<HTTPDocument> document)
		{
			return boost::asio::buffer(document->m_body);
		}

		std::vector<boost::asio::const_buffer> HTTPSerializer::Serialize(std::shared_ptr<HTTPDocument> document)
		{
			std::vector<boost::asio::const_buffer> serializedDocument = this->serializeHeaders(document);

			if (document->m_body.size() > 0)
			{
				serializedDocument.push_back(serializeBody(document));
			}

			return serializedDocument;
		}
	}
}