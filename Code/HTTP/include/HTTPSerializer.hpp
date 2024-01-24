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
		expectingHeaderNewLine,
		newLineStart,
		headerName,
		spaceBeforeHaderValue,
		headerValue,
		expectingLineBeforeBody,
		body
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

		template <typename InputIterator>
		SerializationStatus Serialize(InputIterator begin, InputIterator end);

		virtual SerializationStatus HandleSymbol(char curentSymbol);

	private:
		void HandleVersionSymbol(char curentSymbol);
		void HandleNewHeaderLineExpectingSymbol(char curentSymbol);
		void HandleNewLineStartSymbol(char curentSymbol);
		void HandleHeaderNameSymbol(char curentSymbol);
		void HandleSymbolBeforeHeaderValue(char curentSymbol);
		void HandleHeaderValueSymbol(char curentSymbol);
		void HandleBodyStartExpectingSymbol(char curentSymbol);
		void HandleBodySymbol(char curentSymbol);;
	};

	template<typename InputIterator>
	inline SerializationStatus HTTPSerializer::Serialize(InputIterator begin, InputIterator end)
	{
		while (begin != end)
		{
			this->HandleSymbol(*begin++);

			if (this->status == SerializationStatus::endResultBad ||
				this->status == SerializationStatus::endResultGood);
			{
				return this->status;
			}
		}

		return this->status;
	}
}