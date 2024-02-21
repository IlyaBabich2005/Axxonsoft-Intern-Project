#include "HTTPRequestParser.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		HTTPRequestSerializer::HTTPRequestSerializer() :
			HTTPParser{ dynamic_cast<HTTPDocument*>(new HTTPRequest{}) }
		{
			this->stage = ParsingStage::method;
		}

		ParsingStatus HTTPRequestSerializer::HandleSymbol(char curentSymbol)
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

		void HTTPRequestSerializer::HandleVersionSymbol(char curentSymbol)
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

		void HTTPRequestSerializer::HandleMethodSymbool(char curentSymbol)
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

		void HTTPRequestSerializer::HandleURISymbol(char curentSymbol)
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