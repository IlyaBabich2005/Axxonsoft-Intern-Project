#pragma once

#include "HTTPParser.hpp"
#include "HTTPRequest.hpp"

using std::dynamic_pointer_cast;

namespace AxxonsoftInternProject
{
	namespace http
	{
		class HTTPRequestSerializer : HTTPParser
		{
		private:

		public:
			HTTPRequestSerializer();

			ParsingStatus HandleSymbol(char curentSymbol) override;

			void HandleVersionSymbol(char curentSymbol) override;

		private:
			void HandleMethodSymbool(char curentSymbol);
			void HandleURISymbol(char curentSymbol);

		};
	}
}