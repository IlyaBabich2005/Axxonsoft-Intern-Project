#pragma once

#include "HTTPSerializer.hpp"
#include "HTTPReply.hpp"

namespace http
{
	class HTTPReplySerializer : HTTPSerializer
	{
	public: 
		HTTPReplySerializer();

		SerializationStatus HandleSymbol(char curentSymbol) override;

		void HandleStatusSymbool(char curentSymbol);
		void HandleCodeSymbol(char curentSymbol);
	};
}