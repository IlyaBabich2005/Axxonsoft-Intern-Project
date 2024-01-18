#pragma once

#include "HTTPRequest.hpp"

namespace http
{
	const char spesialCharacters[]
	{
	'(', ')', '<', '>', '@',
	',', ';', ':', '\\', '"',
	'/', '[', ']', '?', '=',
	'{', '}', ' ', '\t',
	};

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
		header_lws,
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

	public:
		HTTPSerializer();

		SerializationStatus GetStage();

		void SetStatus(SerializationStatus status);
		void SetStage(SerializationStage stage);

		virtual SerializationStatus HandleSymble(char curentSymbol) = 0;
		
		bool IsDigid(char symbol);
		bool IsChar(char symbol);
		bool IsControlChar(char symbol);
		bool IsSpesialChar(char symbol);
	};
}