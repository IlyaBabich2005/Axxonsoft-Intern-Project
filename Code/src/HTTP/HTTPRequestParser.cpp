#include "HTTPRequestParser.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		HTTPRequestParcer::HTTPRequestParcer(std::shared_ptr<HTTPRequest> request) :
			HTTPParser{ std::dynamic_pointer_cast<HTTPDocument>(request) }
		{
			m_stage = ParsingStage::method;
		}

		void HTTPRequestParcer::handleSymbol(char curentSymbol)
		{
			__super::handleSymbol(curentSymbol);

			switch (m_stage)
			{
			case method: handleMethodSymbool(curentSymbol); break;
			case uri: handleURISymbol(curentSymbol); break;
			default: break;
			}
		}

		void HTTPRequestParcer::handleVersionSymbol(char curentSymbol)
		{
			if (curentSymbol == '\r')
			{
				m_stage = ParsingStage::expectingHeaderNewLine;
			}
			else if (curentSymbol != '/' && 
				(!AxxonsoftInternProject::checks::characters::IsChar(curentSymbol) || 
					AxxonsoftInternProject::checks::characters::IsControlChar(curentSymbol) ||
					AxxonsoftInternProject::checks::characters::IsSpesialChar(curentSymbol)))
			{
				m_status = ParsingStatus::endResultBad;
			}
			else
			{
				m_document->m_version.push_back(curentSymbol);
			}
		}

		void HTTPRequestParcer::handleMethodSymbool(char curentSymbol)
		{
			if (curentSymbol == ' ')
			{
				m_stage = ParsingStage::uri;
			}
			else if (!AxxonsoftInternProject::checks::characters::IsChar(curentSymbol) || 
				AxxonsoftInternProject::checks::characters::IsControlChar(curentSymbol) || 
				AxxonsoftInternProject::checks::characters::IsSpesialChar(curentSymbol))
			{
				m_status = ParsingStatus::endResultBad;
			}
			else
			{
				std::dynamic_pointer_cast<HTTPRequest>(m_document)->m_method.push_back(curentSymbol);
			}
		}

		void HTTPRequestParcer::handleURISymbol(char curentSymbol)
		{
			if (curentSymbol == ' ')
			{
				m_stage = ParsingStage::httpVersion;
			}
			else if (curentSymbol != ':' && 
					curentSymbol != '/' && 
					(!AxxonsoftInternProject::checks::characters::IsChar(curentSymbol) ||
						AxxonsoftInternProject::checks::characters::IsControlChar(curentSymbol) ||
						AxxonsoftInternProject::checks::characters::IsSpesialChar(curentSymbol))
				)
			{
				m_status = ParsingStatus::endResultBad;
			}
			else
			{
				std::dynamic_pointer_cast<HTTPRequest>(m_document)->m_uri.push_back(curentSymbol);
			}
		}


	}
}