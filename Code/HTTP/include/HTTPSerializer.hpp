#pragma once

#include <memory>

#include "HTTPRequest.hpp"
#include "checks.hpp"

using checks::characters::IsChar,
checks::characters::IsControlChar,
checks::characters::IsDigid,
checks::characters::IsSpesialChar,
std::shared_ptr;

namespace http
{
	enum SerializationStatus
	{
		endResultBad = 0,
		endResultGood, 
		indeterminate
	};

	enum SerializationStage
	{
		method = 0,
		uri,
		httpVersion,
		expectingHeaderNewline,
		NewLineStart,
		headerName,
		spaceBeforeHaderValue,
		headerValue,
		expectingLineBeforeBody,
	};

	class HTTPSerializer
	{
	private:
		SerializationStatus status;
		SerializationStage stage;
		HTTPDocument* document;

	public:
		HTTPSerializer(HTTPDocument* document);
		~HTTPSerializer();

		SerializationStatus GetStage();
		HTTPDocument* GetDocument();

		void SetStatus(SerializationStatus status);
		void SetStage(SerializationStage stage);

		virtual SerializationStatus HandleSymbol(char curentSymbol);

	private:
		void HandleVersionSymbol(char curentSymbol);
		void HandleNewHeaderLineExpectingSymbol(char curentSymbol);
		void HandleNewLineStartSymbol(char curentSymbol);
		void HandleHeaderNameSymbol(char curentSymbol);
		void HandleSymbolBeforeHeaderValue(char curentSymbol);
		void HandleHeaderValueSymbol(char curentSymbol);
	};
}  