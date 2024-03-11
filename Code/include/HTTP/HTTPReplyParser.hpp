#pragma once

#include "HTTPParser.hpp"
#include "HTTPReply.hpp"

namespace AxxonsoftInternProject
{
	namespace http
	{
		class HTTPReplyParser : public HTTPParser
		{
		public:
			HTTPReplyParser(std::shared_ptr<HTTPReply> reply);

		private:
			void handleStatusSymbool(char curentSymbol);
			void handleCodeSymbol(char curentSymbol);
			void handleSymbol(char curentSymbol) override;
			void handleVersionSymbol(char curentSymbol) override;
		};
	}
}