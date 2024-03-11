#pragma once

#include "HTTPParser.hpp"
#include "HTTPRequest.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		class HTTPRequestParcer : public HTTPParser
		{
		private: 

		public:
			HTTPRequestParcer(std::shared_ptr<HTTPRequest> request);

		private:
			void handleMethodSymbool(char curentSymbol);
			void handleURISymbol(char curentSymbol);
			void handleSymbol(char curentSymbol) override;
			void handleVersionSymbol(char curentSymbol) override;

		};
	}
}