#pragma once

#include "HTTPRequest.hpp"

namespace http
{
	enum SerializationStatus
	{
		endResultBad = 0,
		endResultGood, 
		indeterminate
	};


	class HTTPSerializer
	{
	private:
		SerializationStatus status;

	public:
		HTTPSerializer();

		virtual SerializationStatus HandleSymble(char curentSymbol) = 0;
		
		bool IsDigid(char symbol);
		bool IsChar(char symbol);
		bool IsControlChar(char symbol);
		bool IsSpesialChar(char symbol);
	};
}
