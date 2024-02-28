#pragma once

namespace AxxonsoftInternProject
{
	namespace checks
	{
		namespace characters
		{
			const char spesialCharacters[]
			{
			'(', ')', '<', '>', '@',
			',', ';', ':', '\\', '"',
			'/', '[', ']', '?', '=',
			'{', '}', ' ', '\t',
			};

			bool IsDigid(char symbol);
			bool IsChar(char symbol);
			bool IsControlChar(char symbol);
			bool IsSpesialChar(char symbol);
		}
	}
}