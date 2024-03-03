#include "HTTPRequestParser.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		HTTPRequestParcer::HTTPRequestParcer(shared_ptr<HTTPRequest> request) :
			HTTPParser{ dynamic_pointer_cast<HTTPDocument>(request) }
		{
			this->stage = ParsingStage::method;
		}

		void HTTPRequestParcer::HandleSymbol(char curentSymbol)
		{
			__super::HandleSymbol(curentSymbol);

			switch (this->stage)
			{
			case method: this->HandleMethodSymbool(curentSymbol); break;
			case uri: this->HandleURISymbol(curentSymbol); break;
			default: break;
			}
		}

		void HTTPRequestParcer::HandleVersionSymbol(char curentSymbol)
		{
			if (curentSymbol == '\r')
			{
				stage = ParsingStage::expectingHeaderNewLine;
			}
			else if (curentSymbol != '/' && 
				(!IsChar(curentSymbol) || 
				IsControlChar(curentSymbol) || 
				IsSpesialChar(curentSymbol)))
			{
				status = ParsingStatus::endResultBad;
			}
			else
			{
				document->version.push_back(curentSymbol);
			}
		}

		void HTTPRequestParcer::HandleMethodSymbool(char curentSymbol)
		{
			if (curentSymbol == ' ')
			{
				stage = ParsingStage::uri;
			}
			else if (!IsChar(curentSymbol) || IsControlChar(curentSymbol) || IsSpesialChar(curentSymbol))
			{
				status = ParsingStatus::endResultBad;
			}
			else
			{
				dynamic_pointer_cast<HTTPRequest>(this->document)->method.push_back(curentSymbol);
			}
		}

		void HTTPRequestParcer::HandleURISymbol(char curentSymbol)
		{
			if (curentSymbol == ' ')
			{
				this->stage = ParsingStage::httpVersion;
			}
			else if (curentSymbol != ':' && 
					curentSymbol != '/' && 
					(!IsChar(curentSymbol) || 
					IsControlChar(curentSymbol) || 
					IsSpesialChar(curentSymbol))
				)
			{
				this->status = ParsingStatus::endResultBad;
			}
			else
			{
				dynamic_pointer_cast<HTTPRequest>(this->document)->uri.push_back(curentSymbol);
			}
		}


	}
}