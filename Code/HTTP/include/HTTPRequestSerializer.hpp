#pragma once

#include "HTTPSerializer.hpp"
#include "HTTPRequest.hpp"

namespace http
{
	class HTTPRequestSerializer : HTTPSerializer
	{
	private:
		HTTPRequest request;

	public:
		SerializationStatus HandleSymble(char curentSymbol) override;
		
		void HandleMethodSymbool(char curentSymbol);
		void HandleURISymbol(char curentSymbol);
	};
}
