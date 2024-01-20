#pragma once

#include "HTTPSerializer.hpp"
#include "HTTPRequest.hpp"

namespace http
{
	class HTTPRequestSerializer : HTTPSerializer
	{
	private:

	public:
		HTTPRequestSerializer();

		SerializationStatus HandleSymbol(char curentSymbol) override;
		
		void HandleMethodSymbool(char curentSymbol);
		void HandleURISymbol(char curentSymbol);
		
	};
}
