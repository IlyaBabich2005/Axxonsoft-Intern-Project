#pragma once

#include <memory>
#include <iostream>

#include <boost/asio/buffer.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include <boost/format.hpp>

#include "HTTPRequest.hpp"
#include "checks.hpp"

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
			std::shared_ptr<HTTPDocument> m_document;
			ParsingStatus m_status;
			ParsingStage m_stage;
			int m_contentSize;
			int m_handledContentSize;
			std::string m_tempHeaderString;
			bool m_isStringValueReading;
			bool m_isHeaderClassDefined;
			bool m_isHeaserFieldNameDefined;
			bool m_isArgumentString;

		private:
			void handleNewLineStartSymbol(char curentSymbol);
			void handleHeaderNameSymbol(char curentSymbol);
			void handleHeaderValueSymbol(char curentSymbol);
			void handleSymbolBeforeBody(char curentSymbol);
			void handleBodySymbol(char curentSymbol);
			void handleWhiteSpaceSymbolInHeaderValue(char curentSymbol);
			void handleEqualsSymbolInHeaderValue(char curentSymbol);
			void handleCommaSymbolInHeaderValue(char curentSymbol);
			void handleSemicolonSymbolInHeaderValue(char curentSymbol);
			void handleRSymbolInHeaderValue(char curentSymbol);
			void handleNonStringHeaderValueSymbol(char curentSymbol);
			void defineHeaderClass();
			void defineHeaderFieldName();

			void handleSynbolForCorrespondence(char curentSymbol, char requiredSymbol, ParsingStage nextStage);

		protected: 
			virtual void handleSymbol(char curentSymbol);

			virtual void handleVersionSymbol(char curentSymbol) = 0;

		public:
			HTTPParser(std::shared_ptr<HTTPDocument> document);

			template <typename InputIterator>
			ParsingStatus Parse(InputIterator begin, InputIterator end);
		};

		template<typename InputIterator>
		inline ParsingStatus HTTPParser::Parse(InputIterator begin, InputIterator end)
		{
			m_status = indeterminate;

			while (begin != end)
			{
				handleSymbol(*begin++);

				if (m_status == endResultBad ||
					m_status == endResultGood)
				{
					m_stage = httpVersion;
					m_handledContentSize = 0;
					m_contentSize = 0;
					return m_status;
				}
			}

			return m_status;
		}
	}
}