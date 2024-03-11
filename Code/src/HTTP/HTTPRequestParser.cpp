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
				(!charChecks::IsChar(curentSymbol) || 
					charChecks::IsControlChar(curentSymbol) ||
					charChecks::IsSpesialChar(curentSymbol)))
			{
				m_status = ParsingStatus::endResultBad;
			}
			else
			{
				m_document->version.push_back(curentSymbol);
			}
		}

		void HTTPRequestParcer::handleMethodSymbool(char curentSymbol)
		{
			if (curentSymbol == ' ')
			{
				m_stage = ParsingStage::uri;
			}
			else if (!charChecks::IsChar(curentSymbol) || charChecks::IsControlChar(curentSymbol) || charChecks::IsSpesialChar(curentSymbol))
			{
				m_status = ParsingStatus::endResultBad;
			}
			else
			{
				std::dynamic_pointer_cast<HTTPRequest>(m_document)->method.push_back(curentSymbol);
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
					(!charChecks::IsChar(curentSymbol) ||
						charChecks::IsControlChar(curentSymbol) ||
						charChecks::IsSpesialChar(curentSymbol))
				)
			{
				m_status = ParsingStatus::endResultBad;
			}
			else
			{
				std::dynamic_pointer_cast<HTTPRequest>(m_document)->uri.push_back(curentSymbol);
			}
		}


	}
}