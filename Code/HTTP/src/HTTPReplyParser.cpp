#include "HTTPReplyParser.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		HTTPReplySerializer::HTTPReplySerializer() :
			HTTPParser{ dynamic_cast<HTTPDocument*>(new HTTPRequest{}) }
		{
			this->SetStage(ParsingStage::httpVersion);
		}

		ParsingStatus HTTPReplySerializer::HandleSymbol(char curentSymbol)
		{
			__super::HandleSymbol(curentSymbol);

			switch (this->GetStage())
			{
			case code: this->HandleCodeSymbol(curentSymbol); break;
			case httpStatus: this->HandleStatusSymbool(curentSymbol); break;
			default: break;
			}

			return this->GetStage();
		}

		void HTTPReplySerializer::HandleVersionSymbol(char curentSymbol)
		{
			if (curentSymbol == ' ')
			{
				this->SetStage(ParsingStage::code);
			}
			else if (!IsChar(curentSymbol) || IsControlChar(curentSymbol) || IsSpesialChar(curentSymbol))
			{
				this->SetStatus(ParsingStatus::endResultBad);
			}
			else
			{
				this->GetDocument()->version.push_back(curentSymbol);
			}
		}

		void HTTPReplySerializer::HandleStatusSymbool(char curentSymbol)
		{
			if (curentSymbol == '\r')
			{
				this->SetStage(ParsingStage::expectingHeaderNewLine);
			}
			else if (IsChar(curentSymbol) && !IsDigid(curentSymbol) || curentSymbol != ' ')
			{
				shared_ptr<HTTPReply> reply = dynamic_pointer_cast<HTTPReply>(GetDocument());
				reply->status.push_back(curentSymbol);
			}
			else
			{
				this->SetStatus(ParsingStatus::endResultBad);
			}
		}

		void HTTPReplySerializer::HandleCodeSymbol(char curentSymbol)
		{
			if (curentSymbol == ' ')
			{
				this->SetStage(ParsingStage::httpStatus);
			}
			else if (IsDigid(curentSymbol))
			{
				shared_ptr<HTTPReply> reply = dynamic_pointer_cast<HTTPReply>(GetDocument());
				reply->code.push_back(curentSymbol);
			}
			else
			{
				this->SetStatus(ParsingStatus::endResultBad);
			}
		}
	}
}