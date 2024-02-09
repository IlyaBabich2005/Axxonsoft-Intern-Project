#pragma once

#include "HTTPParser.hpp"
#include "HTTPReply.hpp"

using std::dynamic_pointer_cast;

namespace AxxonsoftInternProject
{
	namespace http
	{
		class HTTPReplySerializer : HTTPParser
		{
		public:
			HTTPReplySerializer();

			ParsingStatus HandleSymbol(char curentSymbol) override;

			void HandleVersionSymbol(char curentSymbol) override;

		private:
			void HandleStatusSymbool(char curentSymbol);
			void HandleCodeSymbol(char curentSymbol);
		};
	}
}