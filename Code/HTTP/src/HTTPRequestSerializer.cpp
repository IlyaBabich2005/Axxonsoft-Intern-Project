#include "HTTPRequestSerializer.hpp"

namespace http
{
	SerializationStatus HTTPRequestSerializer::HandleSymble(char curentSymbol)
	{
		switch (this->GetStage())
		{
		case method: 
		default:

		}

		return this->GetStage();
	}

	void HTTPRequestSerializer::HandleMethodSymbool(char curentSymbol)
	{
		if (curentSymbol == ' ')
		{
			this->SetStage(SerializationStage::uri);
		}
		else if(!this->IsChar(curentSymbol) || this->IsControlChar(curentSymbol) || this->IsSpesialChar(curentSymbol))
		{
			this->SetStatus(SerializationStatus::endResultBad);
		}
		else
		{
			this->request.method.push_back(curentSymbol);
		}
	}
	void HTTPRequestSerializer::HandleURISymbol(char curentSymbol)
	{
		if (curentSymbol == ' ')
		{
			this->SetStage(SerializationStage::uri);
		}
		else if (!this->IsChar(curentSymbol) || this->IsControlChar(curentSymbol) || this->IsSpesialChar(curentSymbol))
		{
			this->SetStatus(SerializationStatus::endResultBad);
		}
		else
		{
			this->request.method.push_back(curentSymbol);
		}
	}
}