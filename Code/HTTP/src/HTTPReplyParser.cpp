#include "HTTPReplyParser.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		HTTPReplySerializer::HTTPReplySerializer() :
			HTTPParser{ std::make_shared<HTTPDocument>(new HTTPRequest{}) }
		{
			this->stage = ParsingStage::httpVersion;
		}

		ParsingStatus HTTPReplySerializer::HandleSymbol(char curentSymbol)
		{
			__super::HandleSymbol(curentSymbol);

			switch (this->stage)
			{
			case code: this->HandleCodeSymbol(curentSymbol); break;
			case httpStatus: this->HandleStatusSymbool(curentSymbol); break;
			default: break;
			}

			return this->status;
		}

		void HTTPReplySerializer::HandleVersionSymbol(char curentSymbol)
		{
			if (curentSymbol == ' ')
			{
				this->stage = ParsingStage::code;
			}
			else if (!IsChar(curentSymbol) || IsControlChar(curentSymbol) || IsSpesialChar(curentSymbol))
			{
				this->status = ParsingStatus::endResultBad;
			}
			else
			{
				this->document->version.push_back(curentSymbol);
			}
		}

		void HTTPReplySerializer::HandleStatusSymbool(char curentSymbol)
		{
			if (curentSymbol == '\r')
			{
				this->stage = ParsingStage::expectingHeaderNewLine;
			}
			else if (IsChar(curentSymbol) && !IsDigid(curentSymbol) || curentSymbol != ' ')
			{
				dynamic_pointer_cast<HTTPReply>(document)->status.push_back(curentSymbol);
			}
			else
			{
				this->status = ParsingStatus::endResultBad;
			}
		}

		void HTTPReplySerializer::HandleCodeSymbol(char curentSymbol)
		{
			if (curentSymbol == ' ')
			{
				this->stage = ParsingStage::httpStatus;
			}
			else if (IsDigid(curentSymbol))
			{
				dynamic_pointer_cast<HTTPReply>(this->document)->code.push_back(curentSymbol);
			}
			else
			{
				this->status = ParsingStatus::endResultBad;
			}
		}
	}
}