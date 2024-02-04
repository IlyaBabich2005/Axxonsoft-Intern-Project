#pragma once

#include <boost/asio/buffer.hpp>

#include "HTTPRequest.hpp"
#include "checks.hpp"

using checks::characters::IsChar,
checks::characters::IsControlChar,
checks::characters::IsDigid,
checks::characters::IsSpesialChar;

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
	private:
		ParsingStatus status;
		ParsingStage stage;
		HTTPDocument* document;

	public:
		HTTPParser(HTTPDocument* document);
		~HTTPParser();

		ParsingStatus GetStage();
		HTTPDocument* GetDocument();

		void SetStatus(ParsingStatus status);
		void SetStage(ParsingStage stage);

		template <typename InputIterator>
		ParsingStatus Parse(InputIterator begin, InputIterator end);

		virtual ParsingStatus HandleSymbol(char curentSymbol);

		virtual void HandleVersionSymbol(char curentSymbol) = 0;

	private:
		void HandleNewHeaderLineExpectingSymbol(char curentSymbol);
		void HandleNewLineStartSymbol(char curentSymbol);
		void HandleHeaderNameSymbol(char curentSymbol);
		void HandleSymbolBeforeHeaderValue(char curentSymbol);
		void HandleHeaderValueSymbol(char curentSymbol);
		void HandleBodyStartExpectingSymbol(char curentSymbol);
		void HandleBodySymbol(char curentSymbol);;
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