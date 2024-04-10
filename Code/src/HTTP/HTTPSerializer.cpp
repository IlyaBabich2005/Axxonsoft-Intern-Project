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

				for (int j = 0; j < document->m_headers[i].m_classes.size(); j++)
				{
					if(document->m_headers[i].m_classes[j].m_name != "")
					{
						serializedHeaders.push_back(boost::asio::buffer(document->m_headers[i].m_classes[j].m_name));
						serializedHeaders.push_back(boost::asio::buffer(stock::characters::separators::g_whiteSpaceSeparator));
					}

					for(int k = 0; k < document->m_headers[i].m_classes[j].m_fields.size(); k++)
					{
						if (document->m_headers[i].m_classes[j].m_fields[k].m_name != "")
						{
							serializedHeaders.push_back(boost::asio::buffer(document->m_headers[i].m_classes[j].m_fields[k].m_name));
							serializedHeaders.push_back(boost::asio::buffer(stock::characters::separators::g_httpHeaderValueFieldSeparator));
						}

						for (int l = 0; l < document->m_headers[i].m_classes[j].m_fields[k].m_arguments.size(); l++)
						{
							if (document->m_headers[i].m_classes[j].m_fields[k].m_arguments[l].m_isString)
							{
								serializedHeaders.push_back(boost::asio::buffer(stock::characters::separators::g_doubleQuotes));
							}

							serializedHeaders.push_back(boost::asio::buffer(document->m_headers[i].m_classes[j].m_fields[k].m_arguments[l].m_value));

							if (document->m_headers[i].m_classes[j].m_fields[k].m_arguments.size() != 1 
								&& k != document->m_headers[i].m_classes[j].m_fields[k].m_arguments.size() - 1)
							{
								serializedHeaders.push_back(boost::asio::buffer(stock::characters::separators::g_httpHeaderValueArgumentsSeparator));
							}

							if (document->m_headers[i].m_classes[j].m_fields[k].m_arguments[l].m_isString)
							{
								serializedHeaders.push_back(boost::asio::buffer("\""));
							}
						}

						if (document->m_headers[i].m_classes[j].m_fields.size() != 1 && k != document->m_headers[i].m_classes[j].m_fields.size() - 1)
						{
							serializedHeaders.push_back(boost::asio::buffer(stock::characters::separators::g_httpHeaderValueArgumentsSeparator));
						}
					}

					if (document->m_headers[i].m_classes.size() != 1 && j != document->m_headers[i].m_classes.size() - 1)
					{
						serializedHeaders.push_back(boost::asio::buffer(stock::characters::separators::g_httpHeaderValueSeparator));
					}
					
				}

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
			std::vector<boost::asio::const_buffer> serializedDocument = serializeHeaders(document);
			serializedDocument.push_back(boost::asio::buffer(stock::characters::separators::g_httpDocumentLineSeparator));

			if (document->m_body.size() > 0)
			{
				serializedDocument.push_back(serializeBody(document));
			}

			return serializedDocument;
		}
	}
}