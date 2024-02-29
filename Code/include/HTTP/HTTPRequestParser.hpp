#pragma once

#include "HTTPParser.hpp"
#include "HTTPRequest.hpp"

using std::dynamic_pointer_cast;

namespace AxxonsoftInternProject
{
	namespace http
	{
		class HTTPRequestParcer : public HTTPParser
		{
		private: 

		public:
			HTTPRequestParcer(shared_ptr<HTTPRequest> request);

		private:
			void HandleMethodSymbool(char curentSymbol);
			void HandleURISymbol(char curentSymbol);
			void HandleSymbol(char curentSymbol) override;
			void HandleVersionSymbol(char curentSymbol) override;

		};
	}
}