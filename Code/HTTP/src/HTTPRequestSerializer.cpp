#include "HTTPRequestSerializer.hpp"

namespace http
{
	HTTPRequestSerializer::HTTPRequestSerializer() : 
		HTTPSerializer{ dynamic_cast<HTTPDocument*>(new HTTPRequest{}) }
	{
		this->SetStage(SerializationStage::method);
	}

	SerializationStatus HTTPRequestSerializer::HandleSymbol(char curentSymbol)
	{
		__super::HandleSymbol(curentSymbol);

		switch (this->GetStage())
		{
		case method: this->HandleMethodSymbool(curentSymbol); break;
		case uri: this->HandleURISymbol(curentSymbol); break;
		default: break;
		}

		return this->GetStage();
	}

	void HTTPRequestSerializer::HandleVersionSymbol(char curentSymbol)
	{
		if (curentSymbol == '\r')
		{
			this->SetStage(SerializationStage::expectingHeaderNewLine);
		}
		else if (!IsChar(curentSymbol) || IsControlChar(curentSymbol) || IsSpesialChar(curentSymbol))
		{
			this->SetStatus(SerializationStatus::endResultBad);
		}
		else
		{
			this->GetDocument()->version.push_back(curentSymbol);
		}
	}

	void HTTPRequestSerializer::HandleMethodSymbool(char curentSymbol)
	{
		if (curentSymbol == ' ')
		{
			this->SetStage(SerializationStage::uri);
		}
		else if(!IsChar(curentSymbol) || IsControlChar(curentSymbol) || IsSpesialChar(curentSymbol))
		{
			this->SetStatus(SerializationStatus::endResultBad);
		}
		else
		{
			HTTPRequest* request = (HTTPRequest*)GetDocument();
			request->method.push_back(curentSymbol);
		}
	}

	void HTTPRequestSerializer::HandleURISymbol(char curentSymbol)
	{
		if (curentSymbol == ' ')
		{
			this->SetStage(SerializationStage::httpVersion);
		}
		else if (!IsChar(curentSymbol) || IsControlChar(curentSymbol) || IsSpesialChar(curentSymbol))
		{
			this->SetStatus(SerializationStatus::endResultBad);
		}
		else
		{
			HTTPRequest* request = (HTTPRequest*)GetDocument();
			request->uri.push_back(curentSymbol);
		}
	}

	
}