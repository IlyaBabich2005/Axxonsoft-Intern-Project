#pragma once

#include <memory>

#include <boost/asio/buffer.hpp>

#include "HTTPRequest.hpp"
#include "checks.hpp"

namespace charChecks = AxxonsoftInternProject::checks::characters;

using std::shared_ptr,
	  charChecks::IsChar,
	  charChecks::IsControlChar,
	  charChecks::IsDigid,
	  charChecks::IsSpesialChar;

namespace AxxonsoftInternProject
{
	namespace http
	{
		enum ParsingStatus
		{
			endResultBad = 0,
			endResultGood, 
			indeterminate
		};

		enum ParsingStage
		{
			method = 0,
			uri,
			code,
			httpStatus,
			httpVersion,
			expectingHeaderNewLine,
			newLineStart,
			headerName,
			spaceBeforeHaderValue,
			headerValue,
			expectingLineBeforeBody,
			body
		};

		class HTTPParser
		{
		protected:
			shared_ptr<HTTPDocument> document;
			ParsingStatus status;
			ParsingStage stage;

		private:
			void HandleNewLineStartSymbol(char curentSymbol);
			void HandleHeaderNameSymbol(char curentSymbol);
			void HandleHeaderValueSymbol(char curentSymbol);
			void HandleBodySymbol(char curentSymbol);

			void HandleSynbolForCorrespondence(char curentSymbol, char requiredSymbol, ParsingStage nextStage);

		protected: 
			virtual ParsingStatus HandleSymbol(char curentSymbol);

			virtual void HandleVersionSymbol(char curentSymbol) = 0;

		public:
			HTTPParser(shared_ptr<HTTPDocument> document);

			shared_ptr<HTTPDocument> GetParsingResult();

			template <typename InputIterator>
			ParsingStatus Parse(InputIterator begin, InputIterator end);
		};

		template<typename InputIterator>
		inline ParsingStatus HTTPParser::Parse(InputIterator begin, InputIterator end)
		{
			while (begin != end)
			{
				this->HandleSymbol(*begin++);

				if (this->status == ParsingStatus::endResultBad ||
					this->status == ParsingStatus::endResultGood);
				{
					return this->status;
				}
			}

			return this->status;
		}
	}
}