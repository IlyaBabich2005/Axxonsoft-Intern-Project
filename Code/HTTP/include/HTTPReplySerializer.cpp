#include "HTTPReplySerializer.hpp"

namespace http
{
	HTTPReplySerializer::HTTPReplySerializer() :
		HTTPSerializer{ dynamic_cast<HTTPDocument*>(new HTTPRequest{}) }
	{
	}

	SerializationStatus HTTPReplySerializer::HandleSymbol(char curentSymbol)
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

	void HTTPReplySerializer::HandleStatusSymbool(char curentSymbol)
	{
		if (curentSymbol == '\r')
		{
			this->SetStage(SerializationStage::expectingHeaderNewLine);
		}
		else if (IsChar(curentSymbol) && !IsDigid(curentSymbol) || curentSymbol != ' ')
		{
			HTTPReply* reply = (HTTPReply*)GetDocument();
			reply->status.push_back(curentSymbol);
		}
		else
		{
			this->SetStatus(SerializationStatus::endResultBad);
		}
	}

	void HTTPReplySerializer::HandleCodeSymbol(char curentSymbol)
	{
		if (curentSymbol == ' ')
		{
			this->SetStage(SerializationStage::httpStatus);
		}
		else if (IsDigid(curentSymbol))
		{
			HTTPReply* reply = (HTTPReply*)GetDocument();
			reply->code.push_back(curentSymbol);
		}
		else
		{
			this->SetStatus(SerializationStatus::endResultBad);
		}
	}
}

