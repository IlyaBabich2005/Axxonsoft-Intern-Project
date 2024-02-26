#include "HTTPRequestParser.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		HTTPRequestParcer::HTTPRequestParcer() :
			HTTPParser{ std::make_shared<HTTPDocument>(new HTTPRequest{}) }
		{
			this->stage = ParsingStage::method;
		}

		ParsingStatus HTTPRequestParcer::HandleSymbol(char curentSymbol)
		{
			__super::HandleSymbol(curentSymbol);

			switch (this->stage)
			{
			case method: this->HandleMethodSymbool(curentSymbol); break;
			case uri: this->HandleURISymbol(curentSymbol); break;
			default: break;
			}

			return this->status;
		}

		void HTTPRequestParcer::HandleVersionSymbol(char curentSymbol)
		{
			if (curentSymbol == '\r')
			{
				stage = ParsingStage::expectingHeaderNewLine;
			}
			else if (!IsChar(curentSymbol) || IsControlChar(curentSymbol) || IsSpesialChar(curentSymbol))
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
			else if (!IsChar(curentSymbol) || IsControlChar(curentSymbol) || IsSpesialChar(curentSymbol))
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