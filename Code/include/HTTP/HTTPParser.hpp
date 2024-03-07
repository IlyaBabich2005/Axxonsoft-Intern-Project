#pragma once

#include <memory>
#include <iostream>

#include <boost/asio/buffer.hpp>

#include "HTTPRequest.hpp"
#include "checks.hpp"

namespace charChecks = AxxonsoftInternProject::checks::characters;

using std::shared_ptr,
	  std::exception,
	  std::stoi,
	  stock::headers::names::g_contentLength,
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
			shared_ptr<HTTPDocument> m_document;
			ParsingStatus m_status;
			ParsingStage m_stage;
			int m_contentSize;
			int m_handledContentSize;

		private:
			void handleNewLineStartSymbol(char curentSymbol);
			void handleHeaderNameSymbol(char curentSymbol);
			void handleHeaderValueSymbol(char curentSymbol);
			void handleSymbolBeforeBody(char curentSymbol);
			void handleBodySymbol(char curentSymbol);

			void handleSynbolForCorrespondence(char curentSymbol, char requiredSymbol, ParsingStage nextStage);

		protected: 
			virtual void handleSymbol(char curentSymbol);

			virtual void handleVersionSymbol(char curentSymbol) = 0;

		public:
			HTTPParser(shared_ptr<HTTPDocument> document);

			template <typename InputIterator>
			ParsingStatus Parse(InputIterator begin, InputIterator end);
		};

		template<typename InputIterator>
		inline ParsingStatus HTTPParser::Parse(InputIterator begin, InputIterator end)
		{
			while (begin != end)
			{
				handleSymbol(*begin++);

				if (m_status == endResultBad ||
					m_status == endResultGood)
				{
					return m_status;
				}
			}

			return m_status;
		}
	}
}