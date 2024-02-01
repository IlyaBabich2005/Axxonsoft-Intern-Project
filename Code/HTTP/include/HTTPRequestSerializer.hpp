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

		void HandleVersionSymbol(char curentSymbol) override;
		
	private:
		void HandleMethodSymbool(char curentSymbol);
		void HandleURISymbol(char curentSymbol);
		
	};
}
