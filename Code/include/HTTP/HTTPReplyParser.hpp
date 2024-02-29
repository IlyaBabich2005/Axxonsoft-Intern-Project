#pragma once

#include "HTTPParser.hpp"
#include "HTTPReply.hpp"

using std::dynamic_pointer_cast;

namespace AxxonsoftInternProject
{
	namespace http
	{
		class HTTPReplyParser : public HTTPParser
		{
		public:
			HTTPReplyParser(shared_ptr<HTTPReply> reply);

		private:
			void HandleStatusSymbool(char curentSymbol);
			void HandleCodeSymbol(char curentSymbol);
			void HandleSymbol(char curentSymbol) override;
			void HandleVersionSymbol(char curentSymbol) override;
		};
	}
}