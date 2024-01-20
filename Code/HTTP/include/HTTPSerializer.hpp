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
		expecting_newline_1,
		header_line_start,
		header_name,
		space_before_header_value,
		header_value,
		expecting_newline_2,
		expecting_newline_3
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


	};
}  